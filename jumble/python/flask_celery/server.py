
from app import create_app
# from app import socketio
# from app import app as my_app
from app import socketio

my_app = create_app()

if __name__ == '__main__':
    socketio.run(my_app, debug=True)
