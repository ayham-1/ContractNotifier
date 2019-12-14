#ifndef EXPORT_H
#define EXPORT_H

#include <string>
#include <vector>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "contract.h"
#include "category.h"
#include "db.h"

static auto export_db_as_db(const DB &db, const std::string &filename) -> void {
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << db;
}

#endif
