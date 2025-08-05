#include <pqxx/pqxx>
#include <iostream>

class DatabaseManager{
    public:
        DatabaseManager(std::string db_name, std::string user, std::string password, std::string host, std::string port);
        pqxx::connection db_connection;
        std::string ratings_table_name = "usermovieratings";
        std::string similarity_table_name = "similarities"
        pqxx::result get_all_ratings();

};

DatabaseManager::DatabaseManager(std::string db_name, std::string user, std::string password, std::string host, std::string port){
    std::string connection_string
    this->db_connection("dbname=movrecs user=postgres password=pgpassword host=movrecsdb port=5432");
    if (db_connection.is_open()) {
        std::cout << "Opened database successfully: " << db_connection.dbname() << std::endl;
    } else {
        std::cerr << "Can't open database" << std::endl;
    }
}

