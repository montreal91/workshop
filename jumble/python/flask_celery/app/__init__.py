
from celery import Celery
from flask import Flask
from flask_socketio import SocketIO

from config import broker_url

socketio = SocketIO()
print(socketio.server)

def create_app():
    app = Flask(__name__)

    socketio.init_app(app)
    print(__name__, socketio.server)

    from app.main import main as main_blueprint
    app.register_blueprint(main_blueprint)

    
    return app

def make_celery(app):
    # app = app or create_app()
    celery = Celery(app.name, broker=broker_url)
    celery.conf.update(app.config)
    TaskBase = celery.Task
    class ContextTask(TaskBase):
        abstract = True
        def __call__(self, *args, **kwargs):
            with app.app_context():
                return TaskBase.__call__(self, *args, **kwargs)
    celery.Task = ContextTask
    return celery
