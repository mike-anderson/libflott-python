# LibFlott Python

Python bindings for string comparison of normalized t-information and t-complexity distance from libflott by Niko Rebenich

https://github.com/ardeego/libflott

## Build & Install

```
git submodule update --init
python3 setup.py build
python3 setup.py install --record installed_files.txt
```

to uninstall remove the files recorded in installed_files.txt

## Run

```
import flott
nti_dist = flott.nti_dist("string","strings")
ntc_dist = flott.ntc_dist("string,"strings)
```

## License

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.