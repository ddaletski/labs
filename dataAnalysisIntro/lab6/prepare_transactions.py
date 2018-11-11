import json
import pygraphviz as pgv
import random
import re
import click


def read_classes(path):
    classes = []
    with open(path, 'r') as f:
        for line in f:
            c, prob = re.split(r'\s+', line.strip())
            classes.append((c, float(prob)))

    return classes


def read_rules(path):
    rules = []
    with open(path, 'r') as f:
        for line in f:
            src, dst, prob = re.split(r'\s+', line.strip())
            rules.append((src, dst, float(prob)))

    return rules


def visualize_chains(outpath, classes, rules):
    graph = pgv.AGraph(directed=True, strict=False)

    graph.add_node('initial', shape='octagon', color='steelblue')

    for c, prob in classes:
        graph.add_node(c, shape='ellipse')
        if prob > 0:
            graph.add_edge('initial', c, weight=prob, label=prob, penwidth=int(1 + 2*prob))

    for src, dst, prob in rules:
            graph.add_edge(src, dst, weight=prob, label=prob, penwidth=int(1 + 2*prob))

    graph.graph_attr['overlap'] = 'scale'
    graph.graph_attr['splines'] = True
    graph.graph_attr['ranksep'] = 0.6
    graph.graph_attr['nodesep'] = 0.6
    graph.layout(prog='dot')
    graph.draw(outpath, outpath.split(".")[-1])


def choise_class(classes):
    names, probs = zip(*classes)
    return random.choices(classes, weights=probs)[0]
    

def generate_transactions(n, classes, rules):
    transactions = []
    rules_by_key = {}

    for src, dst, prob in rules:
        rules_by_key.setdefault(src, {})
        rules_by_key[src][dst] = prob

    def create_transaction(candidate):
        transaction = []
        c, _ = candidate
        transaction.append(c)

        if rules_by_key.get(c) is None:
            return transaction

        for new_candidate in rules_by_key[c].items():
            if new_candidate[1] > random.random():
                transaction += create_transaction(new_candidate)

        return transaction

    count = 0
    while count < n:
        transaction = set(sum([create_transaction(c) for c in classes if c[1] > random.random()], []))

        if len(transaction) > 0:
            transactions.append(transaction)
            count += 1

    return transactions
        

@click.command()
@click.option('-c', '--count', default=100, type=int)
def main(count):
    classes = read_classes('classes.txt')
    rules = read_rules('rules.txt')

    visualize_chains("graph.svg", classes, rules)
    transactions = generate_transactions(count, classes, rules)

    with open('trans.csv', 'w') as f:
        for tr in transactions:
            f.write(';'.join(tr) + '\n')

if __name__ == "__main__":
    main()