
const fsys = require("fs");

const db = require("./database");


module.exports = new Object();

module.exports.authors_list = function(request, response) {
  db.get_all_authors((data) => {
    let response_object = new Object();
    response_object.authors = data;
    response.statusCode = 200;
    response.setHeader("Content-Type", "Application/json");
    response.end(JSON.stringify(response_object));
  });
};

module.exports.author_details = function(request, response) {
  db.get_author_by_id(
    request.body.author_id,
    (result) => {
      let response_object = new Object();
      if (result.length === 1) {
        response_object.author = result[0];
      } else {
        response_object.author = null;
      }
      response.statusCode = 200;
      response.setHeader("Content-Type", "Application/json");
      response.end(JSON.stringify(response_object));
    }
  );
};


module.exports.book_details = function(request, response) {
  db.get_book_by_id(
    request.body.book_id,
    (result) => {
      let response_object = new Object();
      if (result.length === 1) {
        response_object.book = result[0];
      } else {
        response_object.book = null;
      }
      response.statusCode = 200;
      response.setHeader("Content-Type", "Application/json");
      response.end(JSON.stringify(response_object));
    }
  );
};

module.exports.books_list = function(request, response) {
  db.get_all_books((data) => {
    let response_object = new Object();
    response_object.books = data;
    response.statusCode = 200;
    response.setHeader("Content-Type", "Application/json");
    response.end(JSON.stringify(response_object));
  });
};

module.exports.create_author = function(request, response) {
  let author = db.create_author_object(
    request.body.first_name,
    request.body.second_name,
    request.body.last_name,
    request.body.bio,
    request.body.book_ids
  );
  db.insert_author(author);
  response.statusCode = 200;
  response.setHeader("Content-Type", "Application/json");
  response.end(JSON.stringify({status: true}));
};

module.exports.create_book = function(request, response) {
  let book = db.create_book_object(
    request.body.title,
    request.body.pub_year,
    request.body.author_ids
  );
  db.insert_book(book);
  response.statusCode = 200;
  response.setHeader("Content-Type", "Application/json");
  response.end(JSON.stringify({status: true}));
};

module.exports.edit_book_authors = function(request, response) {
  db.edit_book_authors(
    request.body.book_id,
    request.body.book_authors,
    request.body.newly_marked_authors,
    request.body.unmarked_authors
  );
  response.statusCode = 200;
  response.setHeader("Content-Type", "Application/json");
  response.end(JSON.stringify({status: true}));
};

module.exports.index = function(request, response) {
  fsys.readFile("index.html", (err, data) => {
    response.statusCode = 200;
    response.setHeader("Content-Type", "text/html");
    response.write(data);
    response.end();
  });
};
