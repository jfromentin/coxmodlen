# Workflow for Caclculco launch

## Compile and generate arg file
python3 scripts/generate.py T N K H

* Example: python3 scripts/generate.py A 8 2 1

## Launch computation
oarsub -S scripts/coxmodlen.oar -p "gpudevice='-1'"


