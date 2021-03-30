import argparse
import os

class ArgParser():
    """
    Class implementing the CLI command parsing logic

    Attributes:
        _parsed_args (argparse.Namespace): would store the parsed arguments
    """

    def __init__(self):
        """ Initialize the parser with argument specifications """
        self._argparser = argparse.ArgumentParser(description='''LARA COM Test Manager''')
        self._parsed_args = None

        self._setup_args()

    def parse_args(self, args):
        """ Parse the given arguments and return them """
        self._parsed_args = self._argparser.parse_args(args)
        return self._parsed_args

    def _setup_args(self):
        """ Specify arguments and their properties """
        # Configure argument parser
        # Dummy group to be able to print a description message for the mutually exclusive group
        dummy_group = self._argparser.add_argument_group(
            "Required options or help-like options which would terminate the program early")
        required_or_help_opts = dummy_group.add_mutually_exclusive_group(required=True)
        required_or_help_opts.add_argument(
            "-s", "--sip-dir",
            help="[REQUIRED] Specify the SIP directory where Vector AMSR bundle exist")

        # # Only effective with a generator control option
        # opt_args_group.add_argument("--src-gen-dir", nargs=1, custom_default_str="<BUILD_DIR>/src-gen",
        #                             metavar='SRC_GEN_DIR', dest='src_gen_dir', action=CustomDefaultHelpAction,
        #                             help="R|[Optional] Specify the generated sources directory.\n"
        #                             "Only effective in combination with --model-dir or --skip-generator-run options.\n"
        #                             "(default: %(custom_default_str)s)")

    def exit(self, status=os.EX_OK, message=None):
        """ Exits the program through the argparser with the given message """
        self._argparser.exit(status=status, message=message)
