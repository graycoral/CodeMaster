from _collections import OrderedDict

def order(keys, obj):
    list_of_tuples = [(key, obj[key]) for key in keys]

    # add all not listed keys
    for key in obj.keys():
        if key not in keys:
            list_of_tuples.append((key, obj[key]))

    return OrderedDict(list_of_tuples)

def wraplist(obj):
    ret = obj
    if isinstance(ret, dict):
        ret = [ret]
    return ret

def switchmachine(required_id):
    if 'ICAS1' in required_id:
        required_id = required_id.replace('ICAS1', 'ICAS3')
    elif 'ICAS3' in required_id:
        required_id = required_id.replace('ICAS3', 'ICAS1')

    return required_id