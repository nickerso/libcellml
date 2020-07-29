%module(package="libcellml") analyserexternalvariable

#define LIBCELLML_EXPORT

%import "types.i"

%feature("docstring") libcellml::AnalyserExternalVariable
"Creates an :class:`AnalyserExternalVariable` object.";

%feature("docstring") libcellml::AnalyserExternalVariable::create
"Creates an :class:`AnalyserExternalVariable` object.";

%feature("docstring") libcellml::AnalyserExternalVariable::variable
"Returns the variable.";

%feature("docstring") libcellml::AnalyserExternalVariable::addDependency
"Adds a dependency to this external variable.";

%feature("docstring") libcellml::AnalyserExternalVariable::removeDependency
"Removes a dependency, specified by an index, name, or with a"
":class:`AnalyserExternalVariable` object. Returns `True` on success.";

%feature("docstring") libcellml::AnalyserExternalVariable::removeAllDependencies
"Removes all dependencies from this external variable.";

%feature("docstring") libcellml::AnalyserExternalVariable::containsDependency
"Tests if a dependency, specified by a name, or with an"
":class:`AnalyserExternalVariable` object, is contained within this external"
"variable.";

%feature("docstring") libcellml::AnalyserExternalVariable::dependency
"Returns the dependency, specified by an index or name.";

%feature("docstring") libcellml::AnalyserExternalVariable::dependencies
"Returns the list of :class:`Variable` objects on which this"
":class:`AnalyserExternalVariable` depends.";

%feature("docstring") libcellml::AnalyserExternalVariable::dependencyCount
"Returns the number of dependencies this external variable contains.";

%{
#include "libcellml/analyserexternalvariable.h"
%}

%typemap(out) libcellml::AnalyserExternalVariable * AnalyserExternalVariable() {
    std::shared_ptr<libcellml::AnalyserExternalVariable> *smartresult = reinterpret_cast<std::shared_ptr<libcellml::AnalyserExternalVariable> *>(result);

    resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_libcellml__AnalyserExternalVariable_t, SWIG_POINTER_NEW | SWIG_POINTER_OWN);
}

%extend libcellml::AnalyserExternalVariable {
    AnalyserExternalVariable(const VariablePtr &variable) {
        auto ptr = new std::shared_ptr<libcellml::AnalyserExternalVariable>(libcellml::AnalyserExternalVariable::create(variable));

        return reinterpret_cast<libcellml::AnalyserExternalVariable *>(ptr);
    }
}

%ignore libcellml::AnalyserExternalVariable::create;

%include "libcellml/types.h"
%include "libcellml/analyserexternalvariable.h"
