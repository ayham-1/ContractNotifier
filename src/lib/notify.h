#ifndef NOTIFY_H
#define NOTIFY_H

#include <ctime>
#include <thread>
#include <mutex>

#include <QDate>
#include <vector>
#include <string>
#include "contract.h"
#include "category.h"
#include "db.h"
#include "password.h"

#include <QSystemTrayIcon>
#include <iostream>
#include <curl/curl.h>
#include <ctime>
#include <cstring>

#define EMAILFORMAT_SUBJECT(name) \
    std::string("WARNING: Contract with name '") + name + std::string("' is near ending.\r\n")

#define EMAILFORMAT_CONTENT(name, desc, expiry, months, days) \
    std::string("This email is automatically generated from ContractNotificator") + std::string(".\r\n") + \
    std::string("Contract Name: ") + name + std::string(".\r\n") + \
    std::string("Contract Description: ") + desc + std::string(".\r\n") + \
    std::string("Contract Expiry Date: ") + expiry + std::string(".\r\n") + \
    std::string("Months remaining until end of contract: ") + std::to_string(months) + std::string(" months, ") + std::to_string(days) + std::string(" days.\r\n") + \
    std::string("Days remaining until end of contract: ") + std::to_string(months*30) + std::to_string(days) + std::string(".\r\n") + \
    std::string("For issues, please report it to: ayhamaboualfadl@gmail.com")

#define NOTIFICATION_SUBJECT(name) \
    std::string("Contract with name '") + name + std::string("' is near ending.")

#define NOTIFICATION_CONTENT(name, expiry) \
    std::string("The contract '") + name + std::string("' expires at: ") + expiry + std::string(".");

static auto notify_sendEmail(const std::string &recipient_addr, const std::string &subject, const std::string &content) -> void;

static auto notify_check(DB &db, bool by_email = true, bool by_notification = true) -> bool {
    // iterate over contracts, and check if there is need to send.
    bool res = false;

    for (int i = 0; i < db._categories.size(); i++) {
        Category &category = db._categories[i];
        for (int j = 0; j < category._contracts.size(); j++) {
            Contract &contract = category._contracts[j];
            QDate current_date = QDate::currentDate();
            QDate expiry_date = contract_getExpiry(contract);
            QDate notify_date = expiry_date;
            notify_date = notify_date.addMonths(-contract._notify_from_months);
            notify_date = notify_date.addDays(-contract._notify_from_days);

            if (current_date >= notify_date) {
                if (!contract._did_notify) {
                    // notify by email.
                    if (by_email)
                        try {
                            notify_sendEmail(db._notifier_email, std::string(EMAILFORMAT_SUBJECT(contract._name)), 
                                    std::string(EMAILFORMAT_CONTENT(contract._name, contract._desc,
                                            contract._expiry, contract._notify_from_months, contract._notify_from_days)));
                        } catch (std::exception &e) {
                            continue;
                        }
                    // notify by notification
                    if (by_notification) {
#ifdef __WIN32__
                        system((std::string("notifu /p \"") + NOTIFICATION_SUBJECT(contract._name) + std::string("\" /m \"") + NOTIFICATION_SUBJECT(contract._expiry) + std::string("\"")).c_str());
#elif defined(__LINUX__)
                        system((std::string("notify-send \"") + NOTIFICATION_SUBJECT(contract._name) + std::string("\" \"") + NOTIFICATION_SUBJECT(contract._expiry) + std::string("\"")).c_str());
#endif
                    }

                    // change states/switches.
                    std::mutex mtx;
                    mtx.lock();
                    contract._did_notify = true;
                    res = true;
                    mtx.unlock();
                }
            }
            if (current_date > expiry_date) {
                // expire the contract.
                std::mutex mtx;
                mtx.lock();
                contract._expired = true;
                category_moveContract(category, db._deactivatedCategory, contract);
                mtx.unlock();
                res = true;
            }
        }
    }
    return res;
}

//////////////////////////////////////
///// Copied from somewhere
//////////////////////////////////////
static std::string payloadText[11];

static std::string dateTimeNow();
static std::string generateMessageId();

static void setPayloadText(const std::string &to,
        const std::string &from,
        const std::string &cc,
        const std::string &nameFrom,
        const std::string &subject,
        const std::string &body) {
    payloadText[ 0] = "Date: "  + dateTimeNow();
    payloadText[ 1] = "To: <"   + to   + ">\r\n";
    payloadText[ 2] = "From: <" + from + "> (" + nameFrom + ")\r\n";
    payloadText[ 3] = "Cc: <"   + cc   + "> (" + nameFrom + ")\r\n";
    payloadText[ 4] = "Message-ID: <" + generateMessageId() + "@" + from.substr(from.find('@') + 1) + ">\r\n";
    payloadText[ 5] = "Subject: " + subject + "\r\n";
    payloadText[ 6] = "\r\n";
    payloadText[ 7] = body + "\r\n";
    payloadText[ 8] = "\r\n";
    payloadText[ 9] = "\r\n"; // "It could be a lot of lines, could be MIME encoded, whatever.\r\n";
    payloadText[10] = "\r\n"; // "Check RFC5322.\r\n";
}

static std::string dateTimeNow() {
    const int RFC5322_TIME_LEN = 32;
    time_t t;
    struct tm *tm;

    std::string ret;
    ret.resize(RFC5322_TIME_LEN);

    time(&t);
    tm = localtime(&t);

    strftime(&ret[0], RFC5322_TIME_LEN, "%a, %d %b %Y %H:%M:%S %z", tm);

    return ret;
}

static std::string generateMessageId()
{
    const int MESSAGE_ID_LEN = 37;
    time_t t;
    struct tm tm;

    std::string ret;
    ret.resize(15);
    ret.reserve(MESSAGE_ID_LEN);

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghi"
        "pqrstuvwxyz";

    while (ret.size() < MESSAGE_ID_LEN) {
        ret += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return ret;
}

struct upload_status { int lines_read; };

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    std::string s = generateMessageId();

    static const char *pt[12] = {};

    for (int i = 0; i < 11; ++i) {
        pt[i] = payloadText[i].c_str();
    }

    pt[11] = NULL;

    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = pt[upload_ctx->lines_read];

    if (data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }

    return 0;
}

static size_t cust_write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
       return size * nmemb;
}

static CURLcode sendEmail(const std::string &to,
        const std::string &from,
        const std::string &cc,
        const std::string &nameFrom,
        const std::string &subject,
        const std::string &body,
        const std::string &url,
        const std::string &password)
{
    CURLcode ret = CURLE_OK;

    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    CURL *curl = curl_easy_init();

    setPayloadText(to, from, cc, nameFrom, subject, body);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cust_write_data);
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L); // 0 disable messages
        curl_easy_setopt(curl, CURLOPT_USERNAME,     from    .c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD,     password.c_str());
        curl_easy_setopt(curl, CURLOPT_URL,          url     .c_str());

        curl_easy_setopt(curl, CURLOPT_USE_SSL,      (long)CURLUSESSL_ALL);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM,    ("<" + from + ">").c_str());
        recipients = curl_slist_append(recipients,   ("<" + to   + ">").c_str());
        recipients = curl_slist_append(recipients,   ("<" + cc   + ">").c_str());

        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT,    recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA,     &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD,       1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE,      1L);

        ret = curl_easy_perform(curl);

        if (ret != CURLE_OK) {
            throw std::runtime_error("curl_easy_perform() failed");
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    return ret;
}
//////////////////////////////////////

static auto notify_sendEmail(const std::string &recipient_addr, const std::string &subject, const std::string &content) -> void {
    if (recipient_addr == "") return;
    std::string email = "contractnotifier@gmail.com";
    std::string smtp = "smtp.gmail.com:587";
    std::string name = "ContractNotifier";
    std::string pass = EMAIL_PASSWORD;
    sendEmail(recipient_addr, email, email, name, subject, content, smtp, pass);
}

#endif
