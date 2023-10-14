import json


class AppConfiguration(object):
    def __init__(self, data=None):
        if data is None:
            with open("fb_data.json") as fh:
                data = json.loads(fh.read())
        else:
            data = dict(data)

        for key, val in data.items():
            setattr(self, key, self.compute_attr_value(val))

    def compute_attr_value(self, value):
        if isinstance(value, list):
            return [self.compute_attr_value(x) for x in value]
        elif isinstance(value, dict):
            return AppConfiguration(value)
        else:
            return value


if __name__ == "__main__":
    instance = AppConfiguration()

    print(instance.name)
    print(instance.hometown.name)
    print(instance.hometown.id)
    print(instance.list[0])
    print(instance.list[1])
    print(instance.list[2])
    print(instance.list[3])
    print(instance.list[4].key)
    print(instance.object.key.key)
    print(instance.foos[0].prop1)
    print(instance.foos[1].prop1)
    for x in range(instance.totalMaquinas):
        print(instance.maquinas[x].name + " " + instance.maquinas[x].IP)
