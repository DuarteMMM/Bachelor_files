from numpy import *
import os
import numpy as np
import matplotlib.pyplot as plt

lists_index = [[] for i in range(5)]
lists_magneticfieldsetpoint = [[] for i in range(1, 6)]
lists_magneticfieldcoilscurrent = [[] for i in range(1, 6)]
lists_biascurrent = [[] for i in range(1, 6)]
lists_outputvoltageaverage = [[] for i in range(1, 6)]
lists_outputvoltagemax = [[] for i in range(1, 6)]
lists_outputvoltagemin = [[] for i in range(1, 6)]
lists_outputvoltagestd = [[] for i in range(1, 6)]
lists_resistance = [[] for i in range(1, 6)]
lists_mr = [[] for i in range(1, 6)]
lists_drdh3pointsdex = [[] for i in range(1, 6)]
lists_dvdh3points = [[] for i in range(1, 6)]
lists_dmrdh3points = [[] for i in range(1, 6)]
lists_drdh2points = [[] for i in range(1, 6)]
lists_dvdh2points = [[] for i in range(1, 6)]
lists_dmrdh2points = [[] for i in range(1, 6)]


# Ciclo de 1 a 5 (inclusive em ambos)
for i in range(1, 6):
    save_path = './Files/' + str(i)

    file_name = str(i) + ".txt"
    file_open = open(file_name, 'r')
    lines = file_open.readlines()

    file_name_index = "Index" + str(i) + ".txt"
    file_name_index = save_path + '/' + file_name_index
    file_open_index = open(file_name_index, 'w+')

    file_name_magneticfieldsetpoint = "MagneticFieldSetPoint" + str(i) + ".txt"
    file_name_magneticfieldsetpoint = os.path.join(save_path, file_name_magneticfieldsetpoint)
    file_open_magneticfieldsetpoint = open(file_name_magneticfieldsetpoint, 'w+')

    file_name_magneticfieldcoilscurrent = "MagneticFieldCoilsCurrent" + str(i) + ".txt"
    file_name_magneticfieldcoilscurrent = os.path.join(save_path, file_name_magneticfieldcoilscurrent)
    file_open_magneticfieldcoilscurrent = open(file_name_magneticfieldcoilscurrent, 'w+')

    file_name_biascurrent = "BiasCurrent" + str(i) + ".txt"
    file_name_biascurrent = os.path.join(save_path, file_name_biascurrent)
    file_open_biascurrent = open(file_name_biascurrent, 'w+')

    file_name_outputvoltageaverage = "OutputVoltageAverage" + str(i) + ".txt"
    file_name_outputvoltageaverage = os.path.join(save_path, file_name_outputvoltageaverage)
    file_open_outputvoltageaverage = open(file_name_outputvoltageaverage, 'w+')

    file_name_outputvoltagemax = "OutputVoltageMax" + str(i) + ".txt"
    file_name_outputvoltagemax = os.path.join(save_path, file_name_outputvoltagemax)
    file_open_outputvoltagemax = open(file_name_outputvoltagemax, 'w+')

    file_name_outputvoltagemin = "OutputVoltageMin" + str(i) + ".txt"
    file_name_outputvoltagemin = os.path.join(save_path, file_name_outputvoltagemin)
    file_open_outputvoltagemin = open(file_name_outputvoltagemin, 'w+')

    file_name_outputvoltagestd = "OutputVoltageSTD" + str(i) + ".txt"
    file_name_outputvoltagestd = os.path.join(save_path, file_name_outputvoltagestd)
    file_open_outputvoltagestd = open(file_name_outputvoltagestd, 'w+')

    file_name_resistance = "Resistance" + str(i) + ".txt"
    file_name_resistance = os.path.join(save_path, file_name_resistance)
    file_open_resistance = open(file_name_resistance, 'w+')

    file_name_mr = "MR" + str(i) + ".txt"
    file_name_mr = os.path.join(save_path, file_name_mr)
    file_open_mr = open(file_name_mr, 'w+')

    file_name_drdh3points = "dRdH3Points" + str(i) + ".txt"
    file_name_drdh3points = os.path.join(save_path, file_name_drdh3points)
    file_open_drdh3points = open(file_name_drdh3points, 'w+')

    file_name_dvdh3points = "dVdH3Points" + str(i) + ".txt"
    file_name_dvdh3points = os.path.join(save_path, file_name_dvdh3points)
    file_open_dvdh3points = open(file_name_dvdh3points, 'w+')

    file_name_dmrdh3points = "dMRdH3Points" + str(i) + ".txt"
    file_name_dmrdh3points = os.path.join(save_path, file_name_dmrdh3points)
    file_open_dmrdh3points = open(file_name_dmrdh3points, 'w+')

    file_name_drdh2points = "DRDH2Points" + str(i) + ".txt"
    file_name_drdh2points = os.path.join(save_path, file_name_drdh2points)
    file_open_drdh2points = open(file_name_drdh2points, 'w+')

    file_name_dvdh2points = "DVDH2Points" + str(i) + ".txt"
    file_name_dvdh2points = os.path.join(save_path, file_name_dvdh2points)
    file_open_dvdh2points = open(file_name_dvdh2points, 'w+')

    file_name_dmrdh2points = "DMRDH2Points" + str(i) + ".txt"
    file_name_dmrdh2points = os.path.join(save_path, file_name_dmrdh2points)
    file_open_dmrdh2points= open(file_name_dmrdh2points, 'w+')

    for j in lines:
        j = j.replace(" ", "")
        j = j.replace("\n", "")
        j = j[:-1] # Remove final comma
        #print ("{}".format(j))
        elements_line = j.split(',')
        for k in range (len(elements_line)):
            if elements_line[k] == "":
                elements_line[k].replace(""," ")
        #print ("{}".format(elements_line))
        file_open_index.write(elements_line[0] + "\n")
        file_open_magneticfieldsetpoint.write(elements_line[1] + "\n")
        file_open_magneticfieldcoilscurrent.write(elements_line[2] + "\n")
        file_open_biascurrent.write(elements_line[3] + "\n")
        file_open_outputvoltageaverage.write(elements_line[4] + "\n")
        file_open_outputvoltagemax.write(elements_line[5] + "\n")
        file_open_outputvoltagemin.write(elements_line[6] + "\n")
        file_open_outputvoltagestd.write(elements_line[7] + "\n")
        file_open_resistance.write(elements_line[8] + "\n")
        file_open_mr.write(elements_line[9] + "\n")
        file_open_drdh3points.write(elements_line[10] + "\n")
        file_open_dvdh3points.write(elements_line[11] + "\n")
        file_open_dmrdh3points.write(elements_line[12] + "\n")
        file_open_drdh2points.write(elements_line[13] + "\n")
        file_open_dvdh2points.write(elements_line[14] + "\n")
        file_open_dmrdh2points.write(elements_line[15] + "\n")

        lists_index[i-1].append(elements_line[0])
        lists_magneticfieldsetpoint[i-1].append(elements_line[1])
        lists_magneticfieldcoilscurrent[i-1].append(elements_line[2])
        lists_biascurrent[i-1].append(elements_line[3])
        lists_outputvoltageaverage[i-1].append(elements_line[4])
        lists_outputvoltagemax[i-1].append(elements_line[5])
        lists_outputvoltagemin[i-1].append(elements_line[6])
        lists_outputvoltagestd[i-1].append(elements_line[7])
        lists_resistance[i-1].append(elements_line[8])
        lists_mr[i-1].append(elements_line[9])
        lists_drdh3pointsdex[i-1].append(elements_line[10])
        lists_dvdh3points[i-1].append(elements_line[11])
        lists_dmrdh3points[i-1].append(elements_line[12])
        lists_drdh2points[i-1].append(elements_line[13])
        lists_dvdh2points[i-1].append(elements_line[14])
        lists_dmrdh2points[i-1].append(elements_line[15])

    # Variables: Index , MagneticFieldSetpoint [Oe], MagneticFieldCoilsCurrent [A], BiasCurrent [A], OutputVoltageAverage [V], OutputVoltageMax [V], OutputVoltageMin [V], OutputVoltageSTD [V], Resistance [Ohm], MR [%], dRdH3Points [Ohm/Oe], dVdH3Points [V/Oe], dMRdH3Points [%/Oe], DRDH2Points [Ohm/Oe], DVDH2Points [V/Oe], DMRDH2Points [%/Oe]
    
    lists_resistance[i-1] = [float(x) / 10000 for x in lists_resistance[i-1]]
    plt.scatter(np.asarray(lists_magneticfieldsetpoint[i-1], float), np.asarray(lists_resistance[i-1], float), c='red')
    plt.xlabel(r'Magnetic field [Oe]', fontsize=13)
    plt.ylabel(r'Resistance [$\times10^4\;\Omega$]', fontsize=13)
    title = "Ensaio " + str(i) + " - Resistance vs. Magnetic Field"
    plt.title(title, fontsize=15, fontweight="bold")
    #plt.grid(which='major', color='0.95', linestyle=':', linewidth=0.8)
    #plt.grid(which='minor', color='0.75', linestyle=':', linewidth=0.6)
    #plt.minorticks_on()
    plt.show()

    lists_outputvoltageaverage[i-1] = [float(x) * 100 for x in lists_outputvoltageaverage[i-1]]
    plt.scatter(np.asarray(lists_magneticfieldsetpoint[i-1], float), np.asarray(lists_outputvoltageaverage[i-1], float), c='black')
    plt.xlabel(r'Magnetic field [Oe]', fontsize=13)
    plt.ylabel(r'Output Voltage Average [$\times10^{-2}\;$V]', fontsize=13)
    title = "Ensaio " + str(i) + " - Output Voltage Average vs. Magnetic Field"
    plt.title(title, fontsize=15, fontweight="bold")
    plt.show()

    plt.scatter(np.asarray(lists_magneticfieldsetpoint[i-1], float), np.asarray(lists_mr[i-1], float), c='blue')
    plt.xlabel(r'Magnetic field [Oe]', fontsize=13)
    plt.ylabel(r'Magnetoresistance [%]', fontsize=13)
    title = "Ensaio " + str(i) + " - Magnetoresistance vs. Magnetic Field"
    plt.title(title, fontsize=15, fontweight="bold")
    plt.show()
