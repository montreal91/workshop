'''
Created on Sep 5, 2018
@author: montreal91
'''

from questions import BasicQuestion
from questions import RelationQuestion


def process_user_input():
    string = input("Ask your question:\n")
    string = string.lower()

    words = string.split(" ")
    if words[0] == "what":
        return BasicQuestion(question=words[0], subject=words[-1])
    elif words[0] == "is":
        return RelationQuestion(
            question=words[0],
            subject=words[1],
            relation=words[-1]
        )
    else:
        raise Exception
