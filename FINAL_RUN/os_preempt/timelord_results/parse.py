import os
import re


def just_time(files):
    result_3072  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_1536  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_768  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }

    for f in files:
        lmp = re.search('lammps', f)
        hpccg = re.search('hpccg', f)
        miniamr = re.search('miniamr', f)
        minife = re.search('minife', f)
        
        is_3072 = re.search('3072', f)
        is_1536 = re.search('1536', f)
        is_768 = re.search('768', f)

        with open(f) as file:
            lines = file.readlines()
            for line in lines:
                if 'real' in line:
                    minute, second =line.strip().split()[1].split('m')
                    sec = 60.0 * int(minute) + float(second.split('s')[0])
                    
                    if lmp and is_3072:
                        result_3072['lammps'].append(sec)
                    if lmp and is_1536:
                        result_1536['lammps'].append(sec)
                    if lmp and is_768:
                        result_768['lammps'].append(sec)

                    if hpccg and is_3072:
                        result_3072['hpccg'].append(sec)
                    if hpccg and is_1536:
                        result_1536['hpccg'].append(sec)
                    if hpccg and is_768:
                        result_768['hpccg'].append(sec)

                    if miniamr and is_3072:
                        result_3072['miniamr'].append(sec)
                    if miniamr and is_1536:
                        result_1536['miniamr'].append(sec)
                    if miniamr and is_768:
                        result_768['miniamr'].append(sec)

                    if minife and is_3072:
                        result_3072['minife'].append(sec)

                    if minife and is_1536:
                        result_1536['minife'].append(sec)

                    if minife and is_768:
                        result_768['minife'].append(sec)
        
    print('3072')
    for key in result_3072:
        if len(result_3072[key]) < 3:
            print(key, '3072 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_3072[key][:3])/3) 
            print('max', max(result_3072[key][:3]))
            print('min', min(result_3072[key][:3]))

    print()
    print()
    print()
    print('1536')

    for key in result_1536:
        if len(result_1536[key]) < 3:
            print(key, ' 1536 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_1536[key][:3])/3)
            print('max', max(result_1536[key][:3]))
            print('min', min(result_1536[key][:3]))
      
    print()
    print()
    print()
    print('768')
    for key in result_768:
        if len(result_768[key]) < 3:
            print(key, '768 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_768[key][:3])/3)
            print('max', max(result_768[key]))
            print('min', min(result_768[key]))

    




def with_tl_ew(files):
    result_3072  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_1536  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_768  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }

    for f in files:
        lmp = re.search('lammps', f)
        hpccg = re.search('hpccg', f)
        miniamr = re.search('miniamr', f)
        minife = re.search('minife', f)
        
        is_3072 = re.search('3072', f)
        is_1536 = re.search('1536', f)
        is_768 = re.search('768', f)

        ew = 0
        with open(f) as file:
            lines = file.readlines()
            for line in lines:
                try:
                    if 'Total extrawork done' in line:
                        ew = int(line.split()[-1])
                        break
                except:
                    continue

            for line in lines:
                if 'real' in line:
                    minute, second =line.strip().split()[1].split('m')
                    sec = 60.0 * int(minute) + float(second.split('s')[0])
            
                    
                    if ew != 0:
                        if lmp and is_3072:
                            result_3072['lammps'].append((sec, ew))
                        if lmp and is_1536:
                            result_1536['lammps'].append((sec, ew))
                        if lmp and is_768:
                            result_768['lammps'].append((sec, ew))

                        if hpccg and is_3072:
                            result_3072['hpccg'].append((sec, ew))
                        if hpccg and is_1536:
                            result_1536['hpccg'].append((sec, ew))
                        if hpccg and is_768:
                            result_768['hpccg'].append((sec, ew))

                        if miniamr and is_3072:
                            result_3072['miniamr'].append((sec, ew))
                        if miniamr and is_1536:
                            result_1536['miniamr'].append((sec, ew))
                        if miniamr and is_768:
                            result_768['miniamr'].append((sec, ew))

                        if minife and is_3072:
                            result_3072['minife'].append((sec, ew))

                        if minife and is_1536:
                            result_1536['minife'].append((sec, ew))

                        if minife and is_768:
                            result_768['minife'].append((sec, ew))
            
    print('3072')
    for key in result_3072:
        if len(result_3072[key]) < 3:
            print(key, '3072 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_3072[key][:3][0])/3) 
            print('max', max(result_3072[key][:3][0]))
            print('min', min(result_3072[key][:3][0]))
            print('EW', sum(result_3072[key][:3][1])/3)

    print()
    print()
    print()
    print('1536')

    for key in result_1536:
        if len(result_1536[key]) < 3:
            print(key, ' 1536 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_1536[key][:3][0])/3)
            print('max', max(result_1536[key][:3][0]))
            print('min', min(result_1536[key][:3][0]))
            print('EW', sum(result_1536[key][:3][1])/3)
      
    print()
    print()
    print()
    print('768')

    for key in result_768:
        if len(result_768[key]) < 3:
            print(key, '768 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_768[key][:3][0])/3)
            print('max', max(result_768[key][:3][0]))
            print('min', min(result_768[key][:3][0]))
            print('EW', sum(result_768[key][:3][1])/3)
def with_ew(files):
    result_3072  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_1536  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }
    result_768  = {'lammps' : [], 'hpccg' : [], 'miniamr': [], 'minife': [] }

    for f in files:
        lmp = re.search('lammps', f)
        hpccg = re.search('hpccg', f)
        miniamr = re.search('miniamr', f)
        minife = re.search('minife', f)
        
        is_3072 = re.search('3072', f)
        is_1536 = re.search('1536', f)
        is_768 = re.search('768', f)

        ew = 0
        with open(f) as file:
            lines = file.readlines()
            for line in lines:
                try:
                    if 'Total Iterations' in line:
                        ew = int(line.split()[-1])
                        break
                except:
                    continue

            for line in lines:
                if 'real' in line:
                    minute, second =line.strip().split()[1].split('m')
                    sec = 60.0 * int(minute) + float(second.split('s')[0])
            
                    
                    if ew != 0:
                        if lmp and is_3072:
                            result_3072['lammps'].append((sec, ew))
                        if lmp and is_1536:
                            result_1536['lammps'].append((sec, ew))
                        if lmp and is_768:
                            result_768['lammps'].append((sec, ew))

                        if hpccg and is_3072:
                            result_3072['hpccg'].append((sec, ew))
                        if hpccg and is_1536:
                            result_1536['hpccg'].append((sec, ew))
                        if hpccg and is_768:
                            result_768['hpccg'].append((sec, ew))

                        if miniamr and is_3072:
                            result_3072['miniamr'].append((sec, ew))
                        if miniamr and is_1536:
                            result_1536['miniamr'].append((sec, ew))
                        if miniamr and is_768:
                            result_768['miniamr'].append((sec, ew))

                        if minife and is_3072:
                            result_3072['minife'].append((sec, ew))

                        if minife and is_1536:
                            result_1536['minife'].append((sec, ew))

                        if minife and is_768:
                            result_768['minife'].append((sec, ew))
            
    print('3072')
    for key in result_3072:
        if len(result_3072[key]) < 3:
            print(key, '3072 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_3072[key][:3][0])/3) 
            print('max', max(result_3072[key][:3][0]))
            print('min', min(result_3072[key][:3][0]))
            print('EW', sum(result_3072[key][:3][1])/3)

    print()
    print()
    print()
    print('1536')

    for key in result_1536:
        if len(result_1536[key]) < 3:
            print(key, ' 1536 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_1536[key][:3][0])/3)
            print('max', max(result_1536[key][:3][0]))
            print('min', min(result_1536[key][:3][0]))
            print('EW', sum(result_1536[key][:3][1])/3)
      
    print()
    print()
    print()
    print('768')

    for key in result_768:
        if len(result_768[key]) < 3:
            print(key, '768 insuffiicent result')
        else:
            print(key)
            print('avg', sum(result_768[key][:3][0])/3)
            print('max', max(result_768[key][:3][0]))
            print('min', min(result_768[key][:3][0]))
            print('EW', sum(result_768[key][:3][1])/3)
files = os.listdir()

tlp = []
ospre = []
baseline = []
fair = []
tl_func = []
y = []
print()
for f in files:
    tlp_match = re.search('tlp', f)
    if tlp_match:
        tlp.append(f)

    ospreempt_match = re.search('os_preempt', f)
    if ospreempt_match:
        ospre.append(f)

    baseline_match = re.search('baseline', f)
    if baseline_match:
        baseline.append(f)


    tlfunc_match = re.search('tl_func', f)
    if tlfunc_match:
        tl_func.append(f)

    yield_match = re.search('yield', f)
    if yield_match:
        y.append(f)


    fair_match = re.search('fair', f)
    if fair_match:
        fair.append(f)

print('========= TL_PREICT ======== ')
with_ew(tlp)
print()
print('========= OS_PREEMPT ======== ')
with_ew(ospre)
print()
print('========= BASELINE ======== ')
just_time(baseline)
print()
print('========= TL_FUNC ======== ')
with_tl_ew(tl_func)
print()
print('========= YIELD ======== ')
just_time(y)
print()
print('========= FAIR ======== ')
just_time(fair)
print()
