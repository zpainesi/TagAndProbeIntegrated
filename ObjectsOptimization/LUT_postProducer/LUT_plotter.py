from optparse import OptionParser
import numpy as np
import math
import os

from matplotlib.colors import ListedColormap, LinearSegmentedColormap
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import mplhep
plt.style.use(mplhep.style.CMS)

parser = OptionParser()
parser.add_option("--inLUT", dest="inLUT", type=str, default=None, help="Input LUT to modify")
parser.add_option("--obj", dest="obj", type=str, default=None, help="Input LUT to modify")
(options, args) = parser.parse_args()


inFile = open(options.inLUT, 'r')

if options.obj =='eg':
    LUT = np.full((16,16,32), np.nan)
    iEt_labels = np.linspace(0, 15, 16, dtype=int)
    inTT_labels = np.linspace(0, 31, 32, dtype=int)
    Xticksshifter = np.linspace(0.5,32-0.5,32)
    Yticksshifter = np.linspace(0.5,16-0.5,16)
else:
    LUT = np.full((4,32,32), np.nan)
    iEt_labels = np.linspace(0, 31, 32, dtype=int)
    inTT_labels = np.linspace(0, 31, 32, dtype=int)
    Xticksshifter = np.linspace(0.5,32-0.5,32)
    Yticksshifter = np.linspace(0.5,32-0.5,32)


started = False
for line in inFile:
    if "start" in line:
        tokens = line.split()
        isoCut = int(tokens[1])
        ieta = int(tokens[14])
        iEt = int(tokens[16])
        inTT = int(tokens[18])

        LUT[ieta][iEt][inTT] = isoCut

        started = True
        continue

    if not started: continue

    if started:
        tokens = line.split()    
        isoCut = int(tokens[1])
        ieta = int(tokens[9])
        iEt = int(tokens[11])
        inTT = int(tokens[13])

        LUT[ieta][iEt][inTT] = min(isoCut, 55)



cmap = cm.get_cmap('tab20c')
#cmap = cm.get_cmap('plasma')
#cmap = cm.get_cmap('viridis')
#cmap = cm.get_cmap('hot')
#cmap = ListedColormap(cmap(np.linspace(0.25, 1, 55)))

# colors = ["#2b9b81", "#fe9b00", "#f4c40f", "#fbe183", "#633372", "#9b3441", "#e6a2a6", "#92c051", "#1f6e9c", "#9f5691", "#e87b89", "#d8443c", "#de597c", "#aa7aa1"]
# colors = ["#fbe183", "#f4c40f", "#fe9b00", "#d8443c", "#9b3441", "#633372"]
# cmap = LinearSegmentedColormap.from_list("mycmap", colors).reversed()
# nodes = [0.0, 0.2, 0.4, 0.6, 1.0]
# cmap = LinearSegmentedColormap.from_list("mycmap", list(zip(nodes,colors)))

# Signac=dict(colors=("#fbe183", "#f4c40f", "#fe9b00", "#d8443c", "#9b3441", "#de597c", "#e87b89", "#e6a2a6", "#aa7aa1", "#9f5691", "#633372", "#1f6e9c", "#2b9b81", "#92c051"), order=(13, 3, 2, 1, 11, 5, 8, 14, 12, 10, 7, 4, 6, 9), colorblind=False),



fig, axs = plt.subplots(2,2, figsize=(80,60))
# plt.subplots_adjust(wspace=0.2)

LUT0 = axs[0][0].pcolormesh(LUT[0], cmap=cmap, edgecolor='black', vmin=np.min(LUT), vmax=np.max(LUT))
colorbar = plt.colorbar(LUT0, ax=axs, ticks=np.linspace(np.min(LUT), np.max(LUT), int(np.max(LUT)-np.min(LUT))+1, dtype=int))
colorbar.ax.tick_params(labelsize=40)
colorbar.set_label(label=r'Iso $E_T$ Cut', fontsize=75)
colorbar.ax.yaxis.set_label_coords(1.5,1)
axs[0][0].set_xticks(Xticksshifter)
axs[0][0].set_xticklabels(inTT_labels, fontsize=40)
axs[0][0].set_yticks(Yticksshifter)
axs[0][0].set_yticklabels(iEt_labels, fontsize=40)
axs[0][0].set_ylabel(r'iEt', fontsize=75)
axs[0][0].set_xlabel(r'inTT', fontsize=75)
axs[0][0].set_title(r'iEta = 0', fontsize=75)
axs[0][0].tick_params(which='both', width=0, length=0)


LUTeta1 = axs[0][1].pcolormesh(LUT[1], cmap=cmap, edgecolor='black', vmin=0, vmax=55)
axs[0][1].set_xticks(Xticksshifter)
axs[0][1].set_xticklabels(inTT_labels, fontsize=40)
axs[0][1].set_yticks(Yticksshifter)
axs[0][1].set_yticklabels(iEt_labels, fontsize=40)
axs[0][1].set_ylabel(r'iEt', fontsize=75)
axs[0][1].set_xlabel(r'inTT', fontsize=75)
axs[0][1].set_title(r'iEta = 1', fontsize=75)
axs[0][1].tick_params(which='both', width=0, length=0)


LUTeta2 = axs[1][0].pcolormesh(LUT[2], cmap=cmap, edgecolor='black', vmin=0, vmax=55)
# colorbar = plt.colorbar(LUTeta2, ax=axs[1])
axs[1][0].set_xticks(Xticksshifter)
axs[1][0].set_xticklabels(inTT_labels, fontsize=40)
axs[1][0].set_yticks(Yticksshifter)
axs[1][0].set_yticklabels(iEt_labels, fontsize=40)
axs[1][0].set_ylabel(r'iEt', fontsize=75)
axs[1][0].set_xlabel(r'inTT', fontsize=75)
axs[1][0].set_title(r'iEta = 2', fontsize=75)
axs[1][0].tick_params(which='both', width=0, length=0)


LUTeta3 = axs[1][1].pcolormesh(LUT[3], cmap=cmap, edgecolor='black', vmin=0, vmax=55)
axs[1][1].set_xticks(Xticksshifter)
axs[1][1].set_xticklabels(inTT_labels, fontsize=40)
axs[1][1].set_yticks(Yticksshifter)
axs[1][1].set_yticklabels(iEt_labels, fontsize=40)
axs[1][1].set_ylabel(r'iEt', fontsize=75)
axs[1][1].set_xlabel(r'inTT', fontsize=75)
axs[1][1].set_title(r'iEta = 3', fontsize=75)
axs[1][1].tick_params(which='both', width=0, length=0)


# mplhep.cms.label(data=False, rlabel='(13.6 TeV)')

fig.savefig(options.inLUT.replace('.txt', '')+'.pdf')

