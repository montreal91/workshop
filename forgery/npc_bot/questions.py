'''
Created on Sep 5, 2018
@author: montreal91
'''

class BasicQuestion(object):
    def __init__(self, subject, question):
        self.subject = subject
        self.question = question


class RelationQuestion(BasicQuestion):
    def __init__(self, subject, question, relation):
        super().__init__(subject, question)
        self.relation = relation
