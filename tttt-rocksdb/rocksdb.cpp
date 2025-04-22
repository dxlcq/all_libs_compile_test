#include <cassert>
#include <iostream>
#include "rocksdb/db.h"

int main() {
    // Open (or create) the database in /tmp/hello_rocksdb
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status =
        rocksdb::DB::Open(options, "/tmp/hello_rocksdb", &db);
    assert(status.ok());

    // Write a key‑value pair
    std::string key = "Hello";
    std::string value = "World";
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());

    // Read it back
    std::string read_value;
    status = db->Get(rocksdb::ReadOptions(), key, &read_value);
    if (status.ok()) {
        std::cout << key << " => " << read_value << std::endl;
    } else {
        std::cerr << "Get failed: " << status.ToString() << std::endl;
    }

    // Delete the key
    status = db->Delete(rocksdb::WriteOptions(), key);
    assert(status.ok());

    // Clean up
    delete db;
    return 0;
}