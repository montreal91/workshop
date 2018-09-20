'''
Created on Sep 5, 2018
@author: montreal91
'''


class KnowledgeNode(object):
    def __init__(self, name):
        self.name = name


    def __repr__(self):
        return "[KB Node] " + str(self.name)


class KnowledgeLink(object):
    SUBCLASS_OF = "subclass_of"
    TYPE_OF = "type_of"


    def __init__(self, subj, relation, obj):
        self.subj = subj
        self.relation = relation
        self.obj = obj


    def __repr__(self):
        s = "{subj} {relation} {obj}"
        return s.format(subj=self.subj, relation=self.relation, obj=self.obj)

# Basic set of classes.
ENTITY = KnowledgeNode("entity")
PERSON = KnowledgeNode("person")
SCIENTIST = KnowledgeNode("scientist")


class KnowledgeGraph(object):
    @staticmethod
    def create_test_graph():
        base = KnowledgeGraph()
        base.add_node(ENTITY)
        base.add_node(PERSON)
        base.add_node(SCIENTIST)
        base.add_link(KnowledgeGraph._create_subclass_link(PERSON, ENTITY))
        base.add_link(KnowledgeGraph._create_subclass_link(SCIENTIST, PERSON))

        heisenberg = KnowledgeNode("heisenberg")
        verner = KnowledgeNode("verner")
        base.add_node(heisenberg)
        base.add_node(verner)

        base.add_link(KnowledgeGraph._create_type_of_link(heisenberg, PERSON))
        base.add_link(KnowledgeGraph._create_type_of_link(heisenberg, SCIENTIST))
        base.add_link(KnowledgeGraph._create_type_of_link(verner, PERSON))

        return base


    def __init__(self):
        self.nodes = []
        self.links = []


    def add_node(self, node):
        self.nodes.append(node)


    def add_link(self, link):
        if link.obj in self.nodes and link.subj in self.nodes:
            self.links.append(link)


    def check_relation(self, subj, relation, obj):
        links = [link for link in self.links if link.relation == relation]
        links = [link for link in links if link.subj == subj]
        print(links, obj)
        links = [link for link in links if link.obj == obj]

        if len(links) == 1:
            return True
        elif len(links) == 0:
            return False
        else:
            raise Exception


    def get_node(self, node_name):
        print(node_name)
        res = [node for node in self.nodes if node.name == node_name]
        if res:
            return res[0]
        else:
            return None


    def get_parent_classes(self, node):
        relations = [rel.obj for rel in self.links if rel.subj == node]
        return relations


    @staticmethod
    def _create_subclass_link(subj, obj):
        return KnowledgeLink(subj, KnowledgeLink.SUBCLASS_OF, obj)


    @staticmethod
    def _create_type_of_link(subj, obj):
        return KnowledgeLink(subj, KnowledgeLink.TYPE_OF, obj)
