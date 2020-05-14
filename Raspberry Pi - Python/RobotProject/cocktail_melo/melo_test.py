listMelodies = [[71, 71, 71], [69, 69, 69], [52, 19, 31], [15, 17, 52], [25, 30, 41]]


def compare_melo(meloTest):
    result = 0
    for i in range(1, len(listMelodies) + 1):
        if meloTest == listMelodies[i-1]:
            result = i
            break
    return result



def melo_play():
    return [15, 17, 52]


#print(compare_melo([52, 19, 31]))
