from optparse import OptionParser
import os

parser = OptionParser()
parser.add_option("--inLUT", dest="inLUT", type=str, default=None, help="Input LUT to modify")
parser.add_option("--type",  dest="type",  type=str, default=None, help="Type of modification: pad, shift, or shiftAndPad?")
(options, args) = parser.parse_args()

if options.type == 'shift' or options.type == 'shiftAndPad':
    print('option not fully supported (works only for egs and not perfectly smoothly)')
    print('exiting')
    exit()

inFile = open(options.inLUT, 'r')

if options.type == "pad":         outTag = "_paddedIsoEt"
if options.type == "shift":       outTag = "_shiftedIsoEt"
if options.type == "shiftAndPad": outTag = "_shiftedAndPaddedIsoEt"

outFile = open(options.inLUT.split('.')[0]+outTag+'.txt', 'w')


if options.type == 'pad':
    started = False
    previousIso = -99
    previousnTT = -99

    for line in inFile:
        if "start" in line: started = True

        # copy header
        if not started:
            outFile.write(line)

        if started:
            tokens = line.split()

            # pad with previous iso if it starts decreasing
            if int(tokens[1]) < previousIso and int(tokens[-1]) > previousnTT:
                tokens[1] = str(previousIso)

            # write the new LUT entries
            last = len(tokens)
            cntr = 0
            for token in tokens:
                cntr += 1
                if cntr < last: outFile.write(token+' ')
                else:           outFile.write(token)

            # add newline
            outFile.write('\n')
            
            # update previous nTT and iso values
            previousIso = int(tokens[1])
            previousnTT = int(tokens[-1])


if options.type == 'shift' or options.type == 'shiftAndPad':
    LUTlines = inFile.readlines()

    started = False
    baseIdx = 0

    for line in LUTlines:
        if "start" in line: break
        outFile.write(line)
        baseIdx += 1

    for i in range(0, 256):
        shiftBy = 0
        previousnTT = 99

        nTTsectionLUT = []
        for idx in range(0, 32):
            nTTsectionLUT.append(LUTlines[baseIdx+idx])

        for idx in range(31, -1, -1):
            tokens = nTTsectionLUT[idx].split()

            if int(tokens[1]) == 1 and int(tokens[-1]) < previousnTT:
                shiftBy +=1
            else:
                break

            # update previous nTT and iso values
            previousnTT = int(tokens[-1])

        new_nTTsectionLUT = []
        for idx in range(31, -1, -1):
            if idx - shiftBy >= 0:
                tokens       = nTTsectionLUT[idx].split()
                tokens_shift = nTTsectionLUT[idx-shiftBy].split()
                tokens[1] = tokens_shift[1]
                new_nTTsectionLUT.append(tokens)

            else:
                tokens = nTTsectionLUT[idx].split()
                tokens[1] = '1'
                new_nTTsectionLUT.append(tokens)

        previousnTT_pad = -99
        previousIso = -99

        for idx in range(31, -1, -1):
            new_tokens = new_nTTsectionLUT[idx]

            if options.type == 'shiftAndPad':
                # pad with previous iso if it starts decreasing
                if int(new_tokens[1]) < previousIso and int(new_tokens[-1]) > previousnTT_pad:
                    new_tokens[1] = str(previousIso)

                previousIso = int(new_tokens[1])
                previousnTT_pad = int(new_tokens[-1])

            for token in new_tokens:
                outFile.write(token+' ')

            # add newline
            outFile.write('\n')

        baseIdx += 32


