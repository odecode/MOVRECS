CREATE TABLE IF NOT EXISTS Users (
	id integer PRIMARY KEY,
	username varchar(20) UNIQUE NOT NULL,
	password varchar(50) NOT NULL,
	email varchar(255) UNIQUE NULL
);

CREATE TABLE IF NOT EXISTS Movies (
	id integer PRIMARY KEY,
	title varchar(255) NOT NULL,
	year_created integer NULL
);

CREATE TABLE IF NOT EXISTS UserMovieRatings (
	user_id INT NOT NULL,
	movie_id INT NOT NULL,
	rating float,
	FOREIGN KEY (user_id) REFERENCES Users (id),
	FOREIGN KEY (movie_id) REFERENCES Movies (id)
);