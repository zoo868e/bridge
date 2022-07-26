from lib import *

def main():
    prefix = "./result/2022/0725_data_1000_called_myGA_best_para_and_corr_"
    suffix = "44002"
    for _cH in range(2):
        for _cS in range(2):
            for _cD in range(2):
                for _cL in range(2):
                    if _cH == _cS == _cD == _cL == 0:
                        continue
                    para = str(_cL) + str(_cD) + str(_cS) + str(_cH)
                    filename = prefix + para + suffix
                    print("Start to edit the", filename)
                    with open(filename, "r") as f:
                        rowdata = [line.rstrip() for line in f]
                    data = [[float(i) for i in row.split(" ")[:-2]] for row in rowdata]
                    max_para = np.max(data, axis = 0)
                    min_para = np.min(data, axis = 0)
                    mean_para = np.mean(data, axis = 0)
                    median_para = np.median(data, axis = 0)
                    std_para = np.std(data, axis = 0)
                    f = open(filename, "a")
                    print("-----------Max----------", file = f)
                    print(" ".join("{:.3f}".format(*t) for t in zip(max_para)), file=f)
                    print("-----------Min----------", file = f)
                    print(" ".join("{:.3f}".format(*t) for t in zip(min_para)), file = f)
                    print("-----------Mean----------", file = f)
                    print(" ".join("{:.3f}".format(*t) for t in zip(mean_para)), file = f)
                    print("-----------Median----------", file = f)
                    print(" ".join("{:.3f}".format(*t) for t in zip(median_para)), file = f)
                    print("-----------Std----------", file = f)
                    print(" ".join("{:.3f}".format(*t) for t in zip(std_para)), file = f)
                    f.close()

if __name__ == "__main__":
    main()
