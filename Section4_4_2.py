from lib import *

def main():
#    import Gameinfo.GA_s4_4_2 as GA
    import Gameinfo.myGA as GA
    import Gameinfo.PSOTLBOd as PTD
    import Gameinfo.problem_lib as plib
    import numpy as np
    from subprocess import Popen, PIPE
    import statistics as stat
    import sys
    data = read("./data/EastOpened.exp")
    Train_target = ["44002"]
    Trained_cp = [1, 1, 1, 0.8, 1, 0.8, 1, 1, 1, 1, 0.8, 1, 1, 0.8, 1, 0.8, 1, 0.8, 1, 0.8, 0.8, 0.8, 1, 1, 0.08]
    Trained_mp = [0.03, 0.02, 0.02, 0.05, 0.05, 0.04, 0.05, 0.01, 0.03, 0.05, 0.05, 0.04, 0.05, 0.05, 0.04, 0.01, 0.02, 0.03, 0.05, 0.03, 0.04, 0.03, 0.05, 0.05, 0.03]
    Trained_keep = [3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 4, 3, 4, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4]
    curve_file_prefix = "./result/2022/thesis/fig_data/0725_data_1000_myGA_called_"
    best_para_prefix = "./result/2022/0725_data_1000_called_myGA_best_para_and_corr_"
    cH_ub[1] = [1 for f in range(called_HCP_size[1])]
    cH_lb[1] = [-1 for f in range(called_HCP_size[1])]
    cL_ub[1] = [1, 13]
    cL_lb[1] = [-1, 0]
    for _formulaid in range(len(Train_target)):
        for _cH in range(2):
            for _cS in range(2):
                for _cD in range(2):
                    for _cL in range(2):
                        if _cH == _cS == _cD == _cL == 0:
                            continue
                        formulaid = str(_cL) + str(_cD) + str(_cS) + str(_cH) + Train_target[_formulaid]
                        best_para = []
                        best_score = []
                        curve = []
                        best_para_file = open(best_para_prefix + str(formulaid), "w")
                        para_size = get_suit_called_formula_para_size(formulaid)
                        para_name = get_suit_formula_name(formulaid)
                        ub = get_suit_called_formula_ub(formulaid)
                        lb = get_suit_called_formula_lb(formulaid)
                        print("ub:", ub, file=sys.stderr)
                        print("lb:", lb, file=sys.stderr)
                        print("Fine-tune methods and the base methods:", para_name, file=sys.stderr)
                        print("Formula id:", formulaid, file=sys.stderr)
                        print("size of ub:", len(ub), file=sys.stderr)
                        print("size of lb:", len(lb), file=sys.stderr)
                        print("size of parameters:", para_size, file=sys.stderr)
                        checkerProcess_train = Popen(['./Called_train', "./data/EastOpened.exp", formulaid], stdin = PIPE, stdout = PIPE)
#                        checkerProcess_train = Popen(['./Called_train', "./data/called_and_ignore_data", formulaid], stdin = PIPE, stdout = PIPE)
                        for _i in range(30):
                            makeDATASET(data, "data/dataForCofsection42", 1000)
                            train_process = Popen(['./Called_train', "data/dataForCofsection42", formulaid], stdin=PIPE, stdout=PIPE)
                            bestScore, best_para, best_curve = GA.GA(plib.ObjfCorr, lb, ub, para_size, 50, 100, Trained_cp[_formulaid], Trained_mp[_formulaid], Trained_keep[_formulaid], train_process)
#                            bestScore, best_para, iters, best_curve = PTD.PSOTLBO(plib.ObjfCorr, lb, ub, para_size, 50, 100, True, formulaid, train_process)
#                            bestScore, best_para, iters, best_curve = GA.GA(GA.ObjfCorr, lb, ub, para_size, 50, 100, True, formulaid, Trained_cp[_formulaid], Trained_mp[_formulaid], Trained_keep[_formulaid])
                            curve.append(best_curve.copy())
                            validate = objf(checkerProcess_train, best_para)
                            best_score.append(validate)
                            print(" ".join(map(str, best_para)), round(bestScore, 3), round(validate, 3), sep = " ", file = best_para_file)
                            print(formulaid, "have run", _i, "times.", file = sys.stderr)
                        curve_file = open(curve_file_prefix + str(formulaid), "w")
                        for x in np.transpose(curve):
                            print(' '.join(map(str, x)), file = curve_file)
                        curve_file.close()
                        best_para_file.close()
                        print(para_name, round(np.max(best_score), 3), round(np.min(best_score), 3), round(np.mean(best_score), 3), round(np.median(best_score), 3), round(np.std(best_score), 3), sep = " & ", end = "\\\\\\hline\n")
                        checkerProcess_train.terminate()

if __name__ == "__main__":
    main()
