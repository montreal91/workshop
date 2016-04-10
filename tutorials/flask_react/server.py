
import json
import os
import time

from flask import Flask, Response, request


app = Flask(__name__, static_url_path='', static_folder='public')
app.add_url_rule('/', 'root', lambda: app.send_static_file('index.html'))


@app.route('/api/comments', methods=['GET', 'POST'])
def comments_handler():
    with open('comments.json', 'r') as file1:
        s = file1.read()
        comments = json.loads(s)

    if request.method == 'POST':
        newComment = request.form.to_dict()
        newComment['id'] = int(time.time() * 1000)
        comments.append(newComment)

        with open('comments.json', 'w') as file1:
            file1.write(json.dumps(comments, indent=4, separators=(',', ': ')))

    return Response(
        json.dumps(comments),
        mimetype='application/json',
        headers={'Cache-Control': 'no-cache', 'Access-Control-Allow-Origin': '*'}
    )

if __name__ == '__main__':
    app.run(port=int(os.environ.get("PORT",3000)))
