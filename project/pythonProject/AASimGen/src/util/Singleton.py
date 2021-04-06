from abc import ABCMeta

# ---------------------------------------------------------------------------------------------------------------------


class Singleton(metaclass=ABCMeta):
    """
    A generic base class to derive any singleton class from.
    """
    __instance = None

    def __new__(cls, *arguments, **keywordArguments):
        """
        Override the __new__ method so that it is a singleton.
        @param cls: The class
        @param arguments: The positional arguments
        @param keyword_arguments: The keyword arguments
        @return Single instance of (derived) singleton class
        """
        if cls.__instance is None:
            cls.__instance = object.__new__(cls)
            cls.__instance.init(*arguments, **keywordArguments)
        return cls.__instance

    def __init__(self, *arguments, **keywordArguments):
        """
        Called every time an instance of the singleton is made
        """
        pass

    def init(self, *arguments, **keywordArguments):
        """
        Function for initialization. This will only be called once regardless of how many instances are created
        @param arguments: The positional arguments
        @param keyword_arguments: The keyword arguments
        """
        pass
