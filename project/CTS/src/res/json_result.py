import json
from collections import OrderedDict

result_data = OrderedDict()


def checkResult(func_name, service, step):
    if func_name not in result_data:
        result_data[func_name] = {}
    result_data[func_name][service+"#"+str(step)] = True


def saveResult():
    with open('result.json', 'w', encoding="utf-8") as result_file:
        json.dump(result_data, result_file, ensure_ascii=False, indent="\t")