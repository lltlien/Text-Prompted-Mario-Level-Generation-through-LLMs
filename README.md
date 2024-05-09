<div align="center">    

# Text-Prompted Mario Level Generation through LLMs
Generated Level
|:-------------------------:
|![alt text](static/timelapse_0.gif)

</div>

Requirements
----
- python 3.8+
- Java 8+ tested

Installation
---------------
from pypi
```
pip install mario-gpt
```

or from source
```
git clone https://github.com/lltlien/Text-Prompted-Mario-Level-Generation-through-LLMs
cd Text-Prompted-Mario-Level-Generation-through-LLMs
python setup.py install
```
Generating Levels
-------------
Minimal code to generate a new level:
```python
import torch
from mario_gpt import MarioLM, SampleOutput
import os, random
from mario_gpt.utils  import  view_level, convert_level_to_png, join_list_of_list, characterize
mario_lm = MarioLM()

# use cuda to speed stuff up
device = torch.device('cuda')
# device = torch.device('cpu')
mario_lm = mario_lm.to(device)

prompts = ["many pipes, many enemies, some blocks, high elevation"]

# generate level of size 1400, pump temperature up to ~2.4 for more stochastic but playable levels
generated_level = mario_lm.sample(
    prompts=prompts,
    num_steps=1400,
    temperature=2.0,
    use_tqdm=True
)

# show string list
generated_level.level

# show PIL image
generated_level.img

# save image
generated_level.img.save("generated_level.png")

# save text level to file
generated_level.save("generated_level.txt")

# play in interactive
generated_level.play()

# run Astar agent
generated_level.run_astar()

# Continue generation
generated_level_continued = mario_lm.sample(
    seed=generated_level,
    prompts=prompts,
    num_steps=1400,
    temperature=2.0,
    use_tqdm=True
)

# load from text file
loaded_level = SampleOutput.load("generated_level.txt")

# play from loaded (should be the same level that we generated)
loaded_level.play()
...
```
Training
-------------
The training class is located [here](mario_gpt/trainer.py), with a small example [notebook](notebooks/Train.ipynb)

```python
import torch
from mario_gpt import MarioDataset, MarioLM, TrainingConfig, MarioGPTTrainer

# create basic gpt model
BASE = "distilgpt2"
mario_lm = MarioLM(lm_path=BASE, tokenizer_path=BASE)

# create dataset
dataset = MarioDataset(mario_lm.tokenizer)

# create training config and trainer
config = TrainingConfig(save_iteration=10)
trainer = MarioGPTTrainer(mario_lm, dataset, config=config)

# train for 100 iterations!
trainer.train(100, batch_size=1)
```

Interacting with Levels
-------------

Using the [play and astar methods](mario_gpt/simulator/simulator.py). For interactive, use the `play()` method and for astar use the `run_astar` method. Example:

```python
from mario_gpt import MarioLM

mario_lm = MarioLM()

prompts = ["many pipes, many enemies, some blocks, high elevation"]

generated_level = mario_lm.sample(
    prompts=prompts,
    num_steps=1400,
    temperature=2.0,
    use_tqdm=True
)

# play in interactive
generated_level.play()

# run Astar agent
generated_level.run_astar()
```
