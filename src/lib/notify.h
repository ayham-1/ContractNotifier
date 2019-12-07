#ifndef NOTIFY_H
#define NOTIFY_H

#include <ctime>
#include <QDate>
#include <vector>
#include <string>
#include "contract.h"
#include "category.h"
#include "db.h"
#include "password.h"

#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <QSystemTrayIcon>
#include <iostream>

#define EMAILFORMAT_SUBJECT(name) \
    std::string("WARNING: Contract with name '") + name + std::string("' is near ending.")

#define EMAILFORMAT_CONTENT(name, desc, expiry, months, days) \
    std::string("This email is automatically generated from ContractNotificator") + std::string(".\r\n") + \
    std::string("Contract Name: ") + name + std::string(".\r\n") + \
    std::string("Contract Description: ") + desc + std::string(".\r\n") + \
    std::string("Contract Expiry Date: ") + expiry + std::string(".\r\n") + \
    std::string("Months remaining until end of contract: ") + std::to_string(months) + std::string(" months, ") + std::to_string(days) + std::string(" days.\r\n") + \
    std::string("Days remaining until end of contract: ") + std::to_string(months*30) + std::to_string(days) + std::string(".\r\n") + \
    std::string("For issues, please report it to: ayhamaboualfadl@gmail.com")

auto notify_sendEmail(const std::string &recipient_addr, const std::string &subject, const std::string &content) -> void;

auto notify_check(DB &db, bool by_email = true, bool by_notification = true) -> void {
    // iterate over contracts, and check if there is need to send.

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
                            std::cout << e.what();
                        }
                    // notify by notification
                    if (by_notification) {
                        // TODO: Implement it.
                        QSystemTrayIcon icon;
                        icon.show();
                        icon.showMessage("This is a test", "Test too");
                    }

                    // change states/switches.
                    contract._did_notify = true;
                }
            }
            if (current_date > expiry_date) {
                // expire the contract.
                contract._expired = true;
                // TODO: Move contract to 'Deactivated' Category.
            }
        }
    }
}

auto notify_sendEmail(const std::string &recipient_addr, const std::string &subject, const std::string &content) -> void {
    using mailio::message;
    using mailio::mail_address;
    using mailio::smtps;
    using mailio::smtp_error;
    using mailio::dialog_error;
    using std::cout;
    using std::endl;

    try {
        message msg;
        msg.from(mail_address("ContractNotifier", "contractnotifier@gmail.com"));// set the correct sender name and address
        msg.add_recipient(mail_address("ContractNotifier", recipient_addr));// set the correct recipent name and address
        msg.subject(subject);
        msg.content(content);

        // connect to server
        smtps conn("smtp.gmail.com", 587);
        // modify username/password to use real credentials
        conn.authenticate("contractnotifier@gmail.com", EMAIL_PASSWORD, smtps::auth_method_t::START_TLS);
        conn.submit(msg);
    }
    catch (smtp_error& exc) {
        throw std::runtime_error(exc.what());
    }
    catch (dialog_error& exc) {
        throw std::runtime_error(exc.what());
    }
}

#endif
