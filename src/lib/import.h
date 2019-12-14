#ifndef IMPORT_H
#define IMPORT_H

#include <string>
#include <vector>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "contract.h"
#include "category.h"
#include "db.h"

static auto import_db_as_db(DB &db, const std::string &filename) -> void {
    std::ifstream ifs(filename, std::ios::out);
    {
        boost::archive::text_iarchive ia(ifs);
        ia >> db;
    }
    ifs.close();
}

#endif
