import collections

class EmptyStack(Exception):
    def __init__(self, method, text="stack is empty"):
        self._method = method
        self._text = text

    def __str__(self):
        return "function %s caused an error: %s" % (str(self._method), self._text)


class ListNode():
    def __init__(self, value, next=None):
        self.val = value
        self.next = next


class StackIterator(collections.Iterator):
    def __init__(self, stack):
        self._stack = stack
        self._node = self._stack._top

    def __iter__(self):
        return self

    def __next__(self):
        if self._node is None:
            raise StopIteration()
        val = self._node.val
        self._node = self._node.next
        return val


class Stack():
    # linked stack class
    def __init__(self):
        self._top = None

    def push(self, val):
        self._top = ListNode(val, self._top)


    def pop(self):
        if self._top is None:
            raise EmptyStack(self.pop)

        val = self._top.val
        self._top = self._top.next

        return val


    def empty(self):
        return self._top is None


    def size(self):
        count = 0
        node = self._top

        while node is not None:
            count += 1
            node = node.next

        return count


    def __iter__(self):
        return StackIterator(self)


if __name__ == "__main__":
    stack = Stack()
    for i in range(10):
        stack.push(i)
        stack.pop()

    for val in stack:
        print(val)

    while not stack.empty():
        print(stack.size(), stack.pop())
