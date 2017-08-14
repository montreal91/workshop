
const http = require("http");
const express = require("express");

const hostname = "127.0.0.1";
const port = 3000;


const app = express();
const bodyParser = require("body-parser");
app.use(express.static("static"));
app.use(bodyParser.json());

const views = require("./views");


app.get("/", views.index);
app.post("/_create_author/", views.create_author);
app.post("/_create_book/", views.create_book);
app.post("/_get_authors_list", views.authors_list);
app.post("/_get_author/", views.author_details);
app.post("/_get_book/", views.book_details);
app.post("/_get_books_list/", views.books_list);
app.post("/_edit_book_authors/", views.edit_book_authors);


const server = app.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
