
import os
basedir = os.path.abspath(os.path.dirname(__file__))

class BaseConfig(object):
    SECRET_KEY = "MY_PRECIOUS"
    DEBUG = True
    BCRYPT_LOG_ROUNDS = 13
    SQLALCHEMY_DATABASE_URI = "sqlite:///" + os.path.join(basedir, "dev.sqlite")
