from lib import *
import sys

def main():
    import Gameinfo.myGA as GA
    from subprocess import Popen, PIPE
    import Gameinfo.problem_lib as plib
    Train_target = ["44002"]
    cache_filename = "Section4.2.2_rewrite_cache"
    curve_file_prefix = "./result/2022/thesis/fig_data/0726_data_5000_myGA_"
    best_para_prefix = "./result/2022/0726_data_5000_myGA_best_para_and_corr_"
    data = read("./data/wholeStaticForC")
    HCP_ub[2] = [0.5, 1, 2, 3, 4]
    long_ub[4] = [4, 13]
    for _formulaid in Train_target:
        checkerProcess_train = Popen(['./subprocesstest', _formulaid, "./data/wholeStaticForC"], stdin = PIPE, stdout = PIPE)
        count_best_para = []
        best_score = []
        para_size = get_suit_formula_para_size(_formulaid)
        para_name = get_suit_formula_name(_formulaid)
        ub = get_suit_formula_ub(_formulaid)
        lb = get_suit_formula_lb(_formulaid)
        curve = []
        best_para_file = open(best_para_prefix + _formulaid, "w", buffering = 1)
        print("ub:", ub, file=sys.stderr)
        print("lb:", lb, file=sys.stderr)
        print("Fine-tune methods and the base methods:", para_name, file=sys.stderr)
        print("Formula id:", _formulaid, file=sys.stderr)
        print("size of ub:", len(ub), file=sys.stderr)
        print("size of lb:", len(lb), file=sys.stderr)
        print("size of parameters:", para_size, file=sys.stderr)
        for i in range(30):
            makeDATASET(data, cache_filename, 5000)
            train_process = Popen(['./subprocesstest', _formulaid, "./Section4.2.2_rewrite_cache"], stdin = PIPE, stdout = PIPE)
            bestScore, best_para, best_curve = GA.GA(plib.ObjfCorr, lb, ub, para_size, 50, 100, 1, 0.03, 3, train_process)
            curve.append(best_curve.copy())
            validate = objf(checkerProcess_train, best_para)
            best_score.append(validate)
            count_best_para.append(best_para.copy())
            print(" ".join("{:.3f}".format(*t) for t in zip(best_para)), "{:.3f}".format(bestScore), "{:.3f}".format(validate), file = best_para_file)
        max_para = np.max(count_best_para, axis = 0)
        min_para = np.min(count_best_para, axis = 0)
        mean_para = np.mean(count_best_para, axis = 0)
        median_para = np.median(count_best_para, axis = 0)
        std_para = np.std(count_best_para, axis = 0)
        print("-----------Max----------", file = best_para_file)
        print(" ".join("{:.3f}".format(*t) for t in zip(max_para)), file = best_para_file)
        print("-----------Min----------", file = best_para_file)
        print(" ".join("{:.3f}".format(*t) for t in zip(min_para)), file = best_para_file)
        print("-----------Mean----------", file = best_para_file)
        print(" ".join("{:.3f}".format(*t) for t in zip(mean_para)), file = best_para_file)
        print("-----------Median----------", file = best_para_file)
        print(" ".join("{:.3f}".format(*t) for t in zip(median_para)), file = best_para_file)
        print("-----------Std----------", file = best_para_file)
        print(" ".join("{:.3f}".format(*t) for t in zip(std_para)), file = best_para_file)
        best_para_file.close()
        curve_file = open(curve_file_prefix + _formulaid, "w", buffering = 1)
        for x in np.transpose(curve):
            print(' '.join(map(str, x)), file = curve_file)
        curve_file.close()
        checkerProcess_train.terminate()

if __name__ == "__main__":
    main()
