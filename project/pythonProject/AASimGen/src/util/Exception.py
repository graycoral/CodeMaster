
class CliError(Exception):
    """
    Generic exception to raise and log different fatal errors.
    """
    def __init__(self, msg, lineNo=None, arxmlFileLine=None):
        """
        Create the exception
        @param msg: A message that will be displayed
        @param lineNo: If provided with traceLine, the lineNo will be displayed in front of the trace line string
        @param traceLine: The string representation of the affected line in the trace file.
        """
        super(CliError).__init__(type(self))

        line = ""
        if arxmlFileLine is not None:
            line = "%i: %s" % (lineNo, arxmlFileLine.decode("utf-8")) if lineNo is not None else arxmlFileLine

        msg = "Error: %s" % msg
        n = max(40, len(msg), len(line))
        self.msg = "\n\n\n" + "=" * n + "\n\n" + msg + "\n\n" + "=" * n

        if arxmlFileLine is not None:
            self.msg += "\nAffected line of arxmlFile:\n\n" + line + "=" * n

    def __str__(self):
        return self.msg

    def __unicode__(self):
        return self.msg
