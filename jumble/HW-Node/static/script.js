
// ctrl stands for controller
const AUTHORS_LIST_PACK = {
  templateUrl: "authors_list.html",
  controller: "authors_list_ctrl"
};

const AUTHOR_DETAIL_PACK = {
  templateUrl: "author_details.html",
  controller: "author_detail_ctrl"
};

const BOOK_DETAIL_PACK = {
  templateUrl: "book_details.html",
  controller: "book_detail_ctrl"
};

const BOOKS_LIST_PACK = {
  templateUrl: "books_list.html",
  controller: "books_list_ctrl"
};

const CREATE_AUTHOR_PACK = {
  templateUrl: "create_author.html",
  controller: "create_author_ctrl"
};

const CREATE_BOOK_PACK = {
  templateUrl: "create_book.html",
  controller: "create_book_ctrl"
};

const EDIT_BOOK_AUTHORS_PACK = {
  templateUrl: "edit_book_authors.html",
  controller: "edit_book_authors_ctrl"
};

const MAIN_PACK = { templateUrl: "main.html" };

const AUTHOR_CREATION_STATUS = "New author is created";
const BOOK_CREATION_STATUS = "New book is created";
const REQUIRED_FIELD_ERROR_MESSAGE = "This field is required";


function _check_author_in_author_list(author_id, book) {
  for (let i=0; i<book.author_ids.length; i++) {
    if (author_id === book.author_ids[i]) {
      return true;
    }
  }
  return false;
}

function _get_new_marked_authors(book, marked_authors) {
  let new_marked_authors = [];
  for (let i=0; i<marked_authors.length; i++) {
    if (marked_authors[i].val) {
      let found = false;
      let a_id = marked_authors[i].id;
      for (let j=0; j < book.author_ids.length; j++) {
        if (a_id === book.author_ids[j]) {
          found = true;
          break;
        }
      }
      if (!found) {
        new_marked_authors.push(a_id);
      }
    }
  }
  return new_marked_authors;
}

function _get_unmarked_authors(book, marked_authors) {
  let unmarked_authors_ids = [];
  for (let i=0; i<book.author_ids.length; i++) {
    let a_id = book.author_ids[i];
    let marked = false;
    for (let j=0; j<marked_authors.length; j++) {
      if (a_id === marked_authors[j].id && marked_authors[j].val) {
        marked = true;
        break;
      }
    }

    if (!marked) {
      unmarked_authors_ids.push(a_id);
    }
  }
  return unmarked_authors_ids;
}

var app = angular.module("bookshelf", ["ngRoute"]);

var authors_list_ctrl = function(scope, protocol) {
  protocol.post("/_get_authors_list/").then((response) => {
    console.log(response.status);
    if (response.data.authors === undefined) {
      scope.authors_list = [];
    } else {
      scope.authors_list = response.data.authors;
    }
  });
};

var author_detail_ctrl = function(scope, protocol, route) {
  let data = new Object();
  data.author_id = route.author_id;
  scope.found = false;
  protocol.post("/_get_author/", data).then((response) => {
    console.log(response.status);
    if (response.data.author !== null ) {
      scope.found = true;
      scope.author = response.data.author;
    } else {
      scope.found = false;
    }
  });
};

var book_detail_ctrl = function(scope, protocol, route) {
  let data = new Object();
  data.book_id = route.book_id;
  scope.found = false;
  protocol.post("/_get_book/", data).then((response) => {
    console.log(response.status);
    if (response.data.book !== null ) {
      scope.found = true;
      scope.book = response.data.book;
    } else {
      scope.found = false;
    }
  });
};

var books_list_ctrl = function(scope, protocol) {
  protocol.post("/_get_books_list/").then((response) => {
    if (response.data.books === undefined) {
      scope.books_list = [];
    } else {
      scope.books_list = response.data.books;
    }
  });
};

var create_author_ctrl = function(scope, protocol) {
  scope.first_name = "Tyler";
  scope.last_name = "Durden";
  scope.author_creation_status = AUTHOR_CREATION_STATUS;
  scope.required_error_message = REQUIRED_FIELD_ERROR_MESSAGE;
  scope.send_author_data = () => {
    let errors = false;
    if (scope.first_name.length === 0) {
      errors = true;
      scope.first_name_required = true;
    } else {
      scope.first_name_required = false;
    }

    if (scope.last_name.length === 0) {
      errors = true;
      scope.last_name_required = true;
    } else {
      scope.last_name_required = false;
    }

    if (errors) {
      scope.response = false;
      return;
    }

    let data = new Object();
    data.first_name = scope.first_name;
    data.second_name = scope.second_name;
    data.last_name = scope.last_name;
    data.bio = scope.bio;
    data.book_ids = [];

    protocol.post("/_create_author", data).then((response) => {
      scope.response = response.data.status;
    });
  }
};

var create_book_ctrl = function(scope, protocol) {
  scope.book_creation_status = BOOK_CREATION_STATUS;
  scope.pub_year = 2010;
  scope.required_error_message = REQUIRED_FIELD_ERROR_MESSAGE;
  scope.response = false;
  scope.title = "";
  
  scope.send_book_data = () => {
    let errors = false;
    console.log(scope.title.length===0);
    if (scope.title.length === 0) {
      errors = true;
      scope.no_title_error = true;
    } else {
      scope.no_title_error = false;
    }

    if (scope.pub_year === null) {
      errors = true;
      scope.no_pub_year_error = true;
    } else {
      scope.no_pub_year_error = false;
    }

    if (errors) {
      scope.response = false;
      return;
    }

    let data = new Object();
    data.title = scope.title;
    data.pub_year = scope.pub_year;
    data.author_ids = [];

    protocol.post("/_create_book/", data).then((response) => {
      scope.response = response.data.status;
    });
  }
};

var edit_book_authors_ctrl = function(scope, protocol, route){
  let data = new Object();
  data.book_id = route.book_id;
  scope.found = false;
  protocol.post("/_get_book/", data).then((response) => {
    if (response.data.book !== null ) {
      scope.found = true;
      scope.book = response.data.book;
    } else {
      scope.found = false;
    }
  });

  protocol.post("/_get_authors_list/").then((response) => {
    if (response.data.authors === undefined) {
      scope.authors_list = [];
    } else {
      scope.authors_list = response.data.authors;
      scope.marked_authors = [];
      for (let i=0; i < scope.authors_list.length; i++) {
        let author_check = new Object();
        author_check.id = scope.authors_list[i]._id;
        author_check.val = _check_author_in_author_list(
          scope.authors_list[i]._id,
          scope.book
        );
        scope.marked_authors.push(author_check);
      }
    }
  });


  scope.send_edited_authors = () => {
    let data = new Object();
    data.book_id = route.book_id;
    data.book_authors = [];
    for (let i=0; i < scope.marked_authors.length; i++) {
      let author_check = scope.marked_authors[i];
      if (author_check.val) {
        data.book_authors.push(author_check.id);
      }
    }
    data.unmarked_authors = _get_unmarked_authors(
      scope.book,
      scope.marked_authors
    );
    data.newly_marked_authors = _get_new_marked_authors(
      scope.book,
      scope.marked_authors
    );
    console.log(data.unmarked_authors);
    protocol.post("/_edit_book_authors/", data).then((response) => {
      console.log(response.status);
    });
  }
};

app.controller(
  AUTHORS_LIST_PACK.controller,
  ["$scope", "$http", authors_list_ctrl]
);

app.controller(
  AUTHOR_DETAIL_PACK.controller,
  ["$scope", "$http", "$routeParams", author_detail_ctrl]
);

app.controller(
  BOOK_DETAIL_PACK.controller,
  ["$scope", "$http", "$routeParams", book_detail_ctrl]
);

app.controller(
  BOOKS_LIST_PACK.controller,
  ["$scope", "$http", books_list_ctrl]
);

app.controller(
  CREATE_AUTHOR_PACK.controller,
  ["$scope", "$http", create_author_ctrl]
);

app.controller(
  CREATE_BOOK_PACK.controller,
  ["$scope", "$http", create_book_ctrl]
);

app.controller(
  EDIT_BOOK_AUTHORS_PACK.controller,
  ["$scope", "$http", "$routeParams", edit_book_authors_ctrl]
);

app.config(function($routeProvider) {
  $routeProvider.when("/", MAIN_PACK);
  $routeProvider.when("/author/:author_id/", AUTHOR_DETAIL_PACK);
  $routeProvider.when("/authors/", AUTHORS_LIST_PACK);
  $routeProvider.when("/book/:book_id/", BOOK_DETAIL_PACK);
  $routeProvider.when("/books/", BOOKS_LIST_PACK);
  $routeProvider.when("/create_author/", CREATE_AUTHOR_PACK);
  $routeProvider.when("/create_book/", CREATE_BOOK_PACK);
  $routeProvider.when("/edit/book/:book_id/", EDIT_BOOK_AUTHORS_PACK);
});
