'''
Created on Sep 5, 2018
@author: montreal91
'''

from input_parser import process_user_input
from knowledge import ENTITY
from knowledge import KnowledgeGraph
from knowledge import KnowledgeLink


def main():
    test_base = KnowledgeGraph.create_test_graph()

    question = process_user_input()
    if question.subject == ENTITY.name:
        print("Congratulations! You've broken everything!")
    elif question.question == "what":
        node = test_base.get_node(question.subject)
        if node is not None:
            answer = test_base.get_parent_classes(node)
            print(answer)
            print(question.subject, "is a", answer[0].name)
        else:
            print("I don't know everything about", question.subject)
    elif question.question == "is":
        node = test_base.get_node(question.subject)
        typeof = test_base.get_node(question.relation)

        if node is None:
            print("I don't know anything about", question.subject)
            return
        elif typeof is None:
            print("I don't know what {obj} is.".format(obj=question.relation))
            return

        answer = test_base.check_relation(
            obj=typeof,
            subj=node,
            relation=KnowledgeLink.TYPE_OF
        )
        if answer:
            print("Yes, {subj} is {obj}.".format(
                subj=question.subject,
                obj=question.relation
            ))
        else:
            print("No, {subj} is not {obj}.".format(
                subj=question.subject,
                obj=question.relation
            ))

if __name__ == "__main__":
    main()
