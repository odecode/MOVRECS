def read_and_return_file_data(filename: str) -> list:
    with open(filename, "r") as file:
        data = file.readlines()
        return data

def create_sql_query(line: list[str]) -> str:
    userid = line[0]
    movieid = line[1]
    rating = int(line[2])
    
    sql_query = "INSERT INTO usermovieratings (user_id,movie_id,rating) VALUES ({},{},{});\n".format(userid,movieid,rating)
    return sql_query

def write_sql_file(queries: list[str]):
    with open("insert_initial_ratings.sql", "w") as file:
        for line in queries:
            file.write(line)

if __name__ == "__main__":
    data = read_and_return_file_data("u.data")
    sql_queries = []
    for line in data:
        line_as_list = line.split("\t")
        line_as_list = line_as_list[:-1]
        query = create_sql_query(line_as_list)
        sql_queries.append(query)
    write_sql_file(sql_queries)