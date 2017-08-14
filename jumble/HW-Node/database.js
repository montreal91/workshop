
const AUTHORS_COLLECTION = "authors";
const BOOKS_COLLECTION = "books";

const mdb_client = require("mongodb").MongoClient;
const ObjectId = require("mongodb").ObjectId;
const mdb_url = "mongodb://localhost:27017/mydb";

mdb_client.connect(mdb_url, (err, db) => {
  if (err) throw err;

  console.log("Database created!");
  db.close();
});

mdb_client.connect(mdb_url, (err, db) => {
  if (err) throw err;
  db.createCollection(BOOKS_COLLECTION, (err, res) => {
    if (err) throw err;
    console.log("Collection `books` is created.");
    db.close();
  });
});

mdb_client.connect(mdb_url, (err, db) => {
  if (err) throw err;
  db.createCollection(AUTHORS_COLLECTION, (err, res) => {
    if (err) throw err;
    console.log("Collection `authors` is created.");
    db.close();
  });
});

function aggregate_objects(collection_name, query, look_up, callback) {
  mdb_client.connect(mdb_url, (err, db) => {
    if (err) throw err;
    db.collection(collection_name).aggregate(
      [
        {
          $match: query
        },{ 
          $lookup: look_up
        }
      ],
      (err, res) => {
        if (err) throw err;
        callback(res);
        db.close();
      }
    );
  });
}

function add_book_to_author(author_id, book_id) {
  mdb_client.connect(mdb_url, (err, db) => {
    db.collection(AUTHORS_COLLECTION).findOne(
      {_id: new ObjectId(author_id)},
      (err, result) => {
        console.log(result);
        result.book_ids.push(new ObjectId(book_id));
        let new_books = { $set: { book_ids: result.book_ids } };
        db.collection(AUTHORS_COLLECTION).updateOne(
          {_id: new ObjectId(author_id)},
          new_books,
          (err1, result1) => {
            if (err1) throw err1;
            console.log("New book is added");
        });
      }
    );
  });
}

function delete_book_from_author(author_id, book_id) {
  console.log(`Deleting book ${book_id} from author ${author_id}`);
  mdb_client.connect(mdb_url, (err, db) => {
    db.collection(AUTHORS_COLLECTION).findOne(
      {_id: new ObjectId(author_id)},
      (err, result) => {
        let oid = new ObjectId(book_id);
        console.log(result);
        let filtered_book_ids = result.book_ids.filter((value) => {
          return !oid.equals(value);
        });
        console.log("=========================================");
        console.log(filtered_book_ids);
        let new_books = { $set: { book_ids: filtered_book_ids } };
        db.collection(AUTHORS_COLLECTION).updateOne(
          {_id: new ObjectId(author_id)},
          new_books,
          (err1, result1) => {
            if (err1) throw err1;
            console.log("Redundant books are removed");
        });
      }
    );
  });
}

function get_all_objects_from_collection(collection_name, callback) {
  mdb_client.connect(mdb_url, (err, db) => {
    if (err) throw err;
    db.collection(collection_name).find({}).toArray(
      (err, result) => {
        if (err) throw err;
        callback(result);
        db.close();
      }
    );
  });
}

function get_object_from_collection_by_id(id, collection_name, callback) {
  mdb_client.connect(mdb_url, (err, db) => {
    if (err) throw err;
    try {
      let oid = new ObjectId(id);
      db.collection(collection_name).findOne(
        {_id: oid},
        (err, result) => {
          if (err) throw err;
          console.log("id: " + id);
          callback(result);
          console.log(result);
          db.close();
        }
      );
    } catch (e) {
      console.log(e);
      callback(null);
    }
  });
}

function insert_object_into_collection(object, collection_name) {
  mdb_client.connect(mdb_url, (err, db) => {
    if (err) throw err;
    db.collection(collection_name).insertOne(object, (err, res) => {
      if (err) throw err;
      db.close();
    });
  });
}

function update_book_authors(book_id, author_ids) {
  let author_object_ids = [];
  for (let i=0; i<author_ids.length; i++) {
    author_object_ids.push(new ObjectId(author_ids[i]));
  }

  let query = { _id: new ObjectId(book_id) };
  let new_authors = { $set: { author_ids: author_object_ids } };

  mdb_client.connect(mdb_url, (err, db) => {
    db.collection(BOOKS_COLLECTION).updateOne(
      query,
      new_authors,
      (err, res) => {
        if (err) throw err;
        console.log(`Book with ${book_id} is updated.`);
        db.close();
      }
    );
  });
}

module.exports = new Object();

module.exports.create_author_object = function (
  first_name,
  second_name,
  last_name,
  bio,
  book_ids
) {
  let author = new Object();
  author.first_name = first_name;
  author.second_name = second_name;
  author.last_name = last_name;
  author.bio = bio;
  author.book_ids = [];
  for (let i=0; i<book_ids.length; i++) {
    author.book_ids.push(new ObjectId(book_ids[i]));
  }
  return author;
}

module.exports.create_book_object = function(title, pub_year, author_ids) {
  let res = new Object();
  res.title = title;
  res.pub_year = pub_year;
  res.author_ids = [];//new ObjectId(authors);
  for (let i =0; i < author_ids.length; i++) {
    res.author_ids.push(new ObjectId(author_ids[i]));
  }
  return res;
}

module.exports.get_all_authors = function(callback) {
  get_all_objects_from_collection(AUTHORS_COLLECTION, callback);
};

module.exports.get_all_books = function(callback) {
  get_all_objects_from_collection(BOOKS_COLLECTION, callback);
};

module.exports.get_author_by_id = function(author_id, callback) {
  try {
    let query = { _id: new ObjectId(author_id) };
    let look_up = new Object();
    look_up.from = BOOKS_COLLECTION;
    look_up.localField = "book_ids";
    look_up.foreignField = "_id";
    look_up.as = "books";

    aggregate_objects(AUTHORS_COLLECTION, query, look_up, callback);
  } catch (e) {
    console.log(e);
  }
};

module.exports.get_book_by_id = function(book_id, callback) {
  try {
    let query = { _id: new ObjectId(book_id) };
    let look_up = new Object();
    look_up.from = AUTHORS_COLLECTION;
    look_up.localField = "author_ids";
    look_up.foreignField = "_id";
    look_up.as = "authors";

    aggregate_objects(BOOKS_COLLECTION, query, look_up, callback);
  } catch (e) {
    console.log(e);
  }
};

module.exports.insert_author = function(author) {
  insert_object_into_collection(author, AUTHORS_COLLECTION);
};

module.exports.insert_book = function(book) {
  insert_object_into_collection(book, BOOKS_COLLECTION);
};

module.exports.edit_book_authors = function(
  book_id,
  author_ids,
  added_authors,
  deleted_authors
) {
  update_book_authors(book_id, author_ids);
};
