"""
Trie-d to implement a Trie with python. :)
Just a try!
"""
class MyTrie(object):
    def __init__(self):
        self.next = dict()
        self.isData = False

    def setData (self):
        self.isData = True

    def insert (self, string):
        print ("Inserting string ",string , " into Trie")
        node = self
        #print ("string ",string)
        for i,ch in enumerate(string):
            #print (i,ch)
            if (ch not in node.next):
                #print ("not present ")
                new = MyTrie()
                node.next[ch] = new
                if (i == len(string)-1):
                    new.setData();
            elif (i == len(string)-1):
                node.setData()
                #print (" present ",node.isData)
            node = node.next[ch]

    def search (self, string):
        print ("Searching ",string)
        node = self
        for i,ch in enumerate(string):
            #print ( i,ch)
            if (ch not in node.next):
                #print ("not present")
                return False
            else:
                #print ("present")
                if (i == len(string)-1):
                    if (node.isData == True):
                        return True;
                node = node.next[ch]
        if (node.isData == True):
            return True
        return False

    def isprefix (self, string):
        print (" Finding Prefix for ",string)
        node = self
        for i,ch in enumerate(string):
            if (ch not in node.next):
                return False
            else:
                node = node.next[ch]
        return True;

    def getNext (self, string):
        print (" Finding Next for string ",string)
        def find_all(node, prev_char, Ans_List):
            if (node.isData == True):
                Ans_List.append(prev_char)
            for ch in node.next:
                find_all(node.next[ch], prev_char+ch, Ans_List)
            return Ans_List

        node = self
        for i,ch in enumerate(string):
            if (ch not in node.next):
                return False
            else:
                node = node.next[ch]
        Ans  = []
        find_all(node, string, Ans)
        print (Ans)

root = MyTrie();
root.insert("apple")
root.insert("app")
root.insert("apw")
root.insert("akw")

print ("\nSearching:")
print(root.search("app"))
print(root.search("apple"))
print(root.search("apw"))
print(root.search("akw"))
print (root.search("z"))


print(root.isprefix("ab"))
print(root.isprefix("ap"))
print (root.isprefix("a"))

print (root.getNext("ap"))
print (root.getNext("a"))
