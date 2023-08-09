def read_and_return_file_data(filename: str) -> list:
    with open(filename, "r") as file:
        data = file.readlines()
        return data

def process_name(fullstr: str) -> list[str]:
    title = fullstr[:-7]
    year = fullstr[-5:-1]
    print(f"PROCESS NAME: {title}        {year}")
    return [title,year]
    
def create_sql_query(line: list[str]) -> str:
    movieid = line[0]
    title = line[1]
    year = line[2]
    title = title.replace("'","")
    sql_query = "INSERT INTO Movies (id,title,year_created) VALUES ({},'{}',{});\n".format(movieid,title,year)
    return sql_query

def write_sql_file(queries: list[str]):
    with open("insert_movie_data.sql", "w") as file:
        for line in queries:
            file.write(line)

if __name__ == "__main__":
    data = read_and_return_file_data("u.item")
    sql_queries = []
    index = 1
    for line in data:
        line_as_list = line.split("|")
        # print(f"LINE AS LIST: {line_as_list}")
        name = line_as_list[1]
        # print(f"NAME:   {name}")
        querydata_firstpart = [index]
        querydata_secondpart = process_name(name)
        querydata = querydata_firstpart + querydata_secondpart
        query = create_sql_query(querydata)
        sql_queries.append(query)
        index += 1
    write_sql_file(sql_queries)