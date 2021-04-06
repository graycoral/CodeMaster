import os
from util.Exception import CliError


# ---------------------------------------------------------------------------------------------------------------------


class ArxmlFileConfiguration:
    """
    TraceFileConfiguration class
    """
    def __init__(self, arxmlFile):
        """
        @param arxmlFile: file name of existing arxmlFile
        """
        if not arxmlFile:
            raise CLIError("Empty filename, cannot create configuration without Tracefile.")
        # -------------------------------------------------------------------------------------------------------------
        # + public attributes (default values)
        # -------------------------------------------------------------------------------------------------------------

        self.outputFolder = ""
        self.arxmlFile = arxmlFile

    def getOutputFolder(self):
        """
        Return the folder where the report output should be placed in
        """
        if self.outputFolder != None and self.outputFolder != "":
            if not os.path.exists(self.outputFolder):
                raise CliError(
                    "Output folder does not exist. Please create folder (%s) and restart." % self.outputFolder
                )
            return self.outputFolder + os.sep

        else:
            return  self.getFilePath() + os.sep

    def getArxmlFileName(self):
        """
        Return the plain name of the trace file without path
        """
        _, tail = os.path.split(self.arxmlFile)
        return tail

    def getFilePath(self):
        """
        Return the plain path of the trace file without filename
        """
        head, _ = os.path.split(self.arxmlFile)
        return head

    def getArxmlName(self):
        """
        Return the plain name of the trace file without extension
        """
        splitted = self.getArxmlFileName().split(".")
        splitted.pop()
        return ".".join(splitted)

