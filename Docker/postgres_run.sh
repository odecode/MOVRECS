docker run -p 5432:5432 -d --name movrecsdb \
    -e POSTGRES_PASSWORD=pgpassword \
    -e POSTGRES_USER=postgres \
    -e POSTGRES_DB=movrecs \
    -v pgdata:/var/lib/postgresql/data \
    postgres

until docker exec movrecsdb pg_isready -h localhost -p 5432 -U postgres > /dev/null 2>&1; do
    echo "Waiting for the PostgreSQL container to start..."
    sleep 2
done

docker exec -u postgres movrecsdb psql createdb -U postgres movrecs

docker cp create_tables.sql movrecsdb:create_tables.sql
docker cp insert_user_data.sql movrecsdb:insert_user_data.sql
docker cp insert_movie_data.sql movrecsdb:insert_movie_data.sql
docker cp insert_initial_ratings.sql movrecsdb:insert_initial_ratings.sql

docker exec -u postgres movrecsdb psql movrecs postgres -a -f ./create_tables.sql
docker exec -u postgres movrecsdb psql movrecs postgres -a -f ./insert_user_data.sql
docker exec -u postgres movrecsdb psql movrecs postgres -a -f ./insert_movie_data.sql
docker exec -u postgres movrecsdb psql movrecs postgres -a -f ./insert_initial_ratings.sql
    