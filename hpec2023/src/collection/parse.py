import os


def parse(filename, app, proc):
    with open(proc + '/' +filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            if 'real' in line:
                minute, second =line.strip().split()[1].split('m')
                sec = 60.0 * int(minute) + float(second.split('s')[0])
                return sec

        assert("no found")
        return 0
        
    

enum = {"768": 0 , "1536": 1, "3072": 2}
group = {};
for process in ["768", "1536", "3072"]:
    for filename in os.listdir(process):
        app = filename.split("_")[0]
        if app in group:
            group[app].append(filename)
        else:
            group[app] = [filename]


print()
for app in group:
    baseline_sum = [0.0,0.0,0.0]
    yield_sum = [0.0,0.0,0.0]
    tl_sum = [0.0,0.0,0.0]
    proc_sum = [0.0,0.0,0.0]
    print('Application:', app)
    for filename in group[app]:
        app = filename.split("_")[0]
        typ = filename.split("_")[1]
        proc = filename.split("_")[2]
        if typ == 'baseline':
            baseline_sum[enum[proc]] += parse(filename, app, proc)
        elif typ == 'yield':
            yield_sum[enum[proc]] += parse(filename, app, proc)
        elif typ == 'tl':
            tl_sum[enum[proc]] += parse(filename, app, proc)
        else:
            proc_sum[enum[proc]] += parse(filename, app, proc)


    print("Baseline time")
    for b, proc in zip(baseline_sum, enum.keys()):
        print(proc, b/3)

    print()

    print("Yield time")
    for b, proc in zip(yield_sum, enum.keys()):
        print(proc, b/3)

    print()
    print("TL-Func time")
    for b, proc in zip(tl_sum, enum.keys()):
        print(proc, b/3)

    print()
    print("TL-Proc time")
    for b, proc in zip(proc_sum, enum.keys()):
        print(proc, b/3)

    print("============\n")
