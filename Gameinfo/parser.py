import sys

def parse_score(row_score):
    data = row_score.split(";")
    ret = []
    one_suit = []
    for i in range(len(data)):
        one_suit.clear()
        score = data[i].split(",")
        for score_idx in range(len(score)):
            one_suit.append(float(score[score_idx]))
        ret.append(one_suit.copy())
    return ret

def parse_score_matrix_file(filename):
    f = open(filename)
    rowdata = f.read()
    f.close()
    data = rowdata.splitlines()
    ret = []
    one_matrix = []
    for i in data:
        one_matrix.clear()
        name = i.split(":")[0]
        score = i.split(":")[1]
        forNT = score.split("@")[1]
        forSuit = score.split("@")[0]
        one_matrix.append(name)
        one_matrix.append(parse_score(forSuit).copy())
        one_matrix.append(parse_score(forNT).copy())
        ret.append(one_matrix.copy())
    return ret

def parse_result_score(filename):
    f = open(filename)
    rowdata = f.read()
    f.close()
    data = rowdata.splitlines()
    ret = []
    temp = []
    for i in data:
        if i[0] == '-':
            ret.append(temp.copy())
            temp.clear()
            continue
        if i[0] == 'H':
            temp.append(i)
        else:
            temp.append(float(i))
    return ret

if __name__ == "__main__":
    result = parse_result_score("./09151116")
    for i in result:
        print(i)
