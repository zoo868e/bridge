from lib import *
def main():
    import Gameinfo.GA_NT as GA
    import Gameinfo.parser as ps
    import numpy as np
    from subprocess import Popen, PIPE
    import statistics as stat
    import sys
    """
    data
    """
    dataset = "./data/Static_NT_DDS_forC.exp"
    trainingF = "./data/NT_training_data"
    data = read(dataset)
    curve_file_prefix = "./result/2022/thesis/fig_data/0719_NT_"
    best_para_prefix = "./result/2022/0719_best_para_"
    for _H in range(2):
        for _L in range(2):
            for _S in range(2):
                if _H == _L == _S == 0:
                    continue
                formulaid = str(_S) + str(_L) + str(_H)
                para_name = get_NT_formula_name(formulaid)
                ub = NT_HCP_ub[_H] + NT_long_ub[_L] + NT_short_ub[_S]
                lb = NT_HCP_lb[_H] + NT_long_lb[_L] + NT_short_lb[_S]
                para_size = get_NT_formula_para_size(formulaid)
                checkerProcess_train = Popen(['./NT_scorer', dataset, formulaid], stdin=PIPE, stdout=PIPE)
                best_para = []
                curve = []
                best_score = []
                best_para_file = open(best_para_prefix + str(formulaid), "w")
                for i in range(30):
                    makeDATASET(data, trainingF, 10)
                    tmp = GA.GA(GA.ObjfCorr, lb, ub, para_size, 50, 100, True, formulaid, trainingF, 1, 0.01, 1)
                    curve.append(tmp[3].copy())
                    output = ""
                    for a in tmp[1]:
                        output += str(a) + " "
                    validate = round(objf(checkerProcess_train, tmp[1]), 3)
                    best_score.append(validate)
                    output += str(round(tmp[0], 3)) + " " + str(validate)
                    print(output, file = best_para_file, buffering=1)
                    print(formulaid, "have run", i, "times.", file=sys.stderr, buffering = 1)
                curve_file = open(curve_file_prefix + str(formulaid), "w")
                for x in np.transpose(curve):
                    print(' '.join(map(str, x)), file = curve_file, buffering = 1)
                curve_file.close()
                best_para_file.close()
                print(para_name, round(np.max(best_score), 3), round(np.min(best_score), 3), round(np.mean(best_score), 3), round(np.median(best_score), 3), round(np.std(best_score), 3), sep = " & ", end = "\\\\\\hline\n", buffering = 1)


if __name__ == "__main__":
    main()
