"""Load dependencies needed to compile the project."""


load("//third_party/fmt:workspace.bzl", fmt = "repo")
load("//third_party/spdlog:workspace.bzl", spdlog = "repo")
load("//third_party/catch2:workspace.bzl", catch2 = "repo")



def initialize_third_party():
    """Load common dependencies."""
    
    fmt()
    spdlog()
    catch2()
    
    
