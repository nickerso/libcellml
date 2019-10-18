/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(Generator, isolatedFirstOrderModel)
{
    // This test resulted from https://github.com/cellml/libcellml/issues/432

    //  1.a   Create the model instance
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("Tutorial4_FirstOrderModel");

    //  1.b   Create a component and add it into the model
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    component->setName("IonChannel");
    model->addComponent(component);

    //  2.a   Define the mathematics.
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";

    // dy/dt = alpha_y*(1-y) - beta_y*y
    std::string equation1 =
        "<apply>\
            <eq/>\
            <apply>\
                <diff/>\
                <bvar>\
                    <ci>t</ci>\
                </bvar>\
                <ci>y</ci>\
            </apply>\
            <apply>\
                <minus/>\
                <apply>\
                    <times/>\
                    <ci>alpha_y</ci>\
                    <apply>\
                        <minus/>\
                        <cn cellml:units=\"dimensionless\">1</cn>\
                        <ci>y</ci>\
                    </apply>\
                </apply>\
                <apply>\
                    <times/>\
                    <ci>beta_y</ci>\
                    <ci>y</ci>\
                </apply>\
            </apply>\
        </apply>";
    // i_y = g_y*power(y,gamma)*(V-E_y)
    std::string equation2 =
        "<apply>\
            <eq/>\
            <ci>i_y</ci>\
            <apply>\
                <times/>\
                <ci>g_y</ci>\
                <apply>\
                    <minus/>\
                    <ci>V</ci>\
                    <ci>E_y</ci>\
                </apply>\
                <apply>\
                    <power/>\
                    <ci>y</ci>\
                    <ci>gamma</ci>\
                </apply>\
            </apply>\
        </apply>";
    std::string mathFooter = "</math>";

    //  2.b   Add the maths to the component.  Note that there is only one maths
    //        string stored, so parts which are appended must create a viable
    //        MathML2 string when concantenated.  To clear any string which is
    //        already stored, simply call setMath("") with an empty string.
    component->setMath(mathHeader);
    component->appendMath(equation1);
    component->appendMath(equation2);
    component->appendMath(mathFooter);

    //  3.a,b Declaring the variables, their names, units, and initial conditions
    //        Note that the names given to variables must be the same as that used
    //        within the <ci> blocks in the MathML string we created in step 2.a.

    libcellml::VariablePtr t = std::make_shared<libcellml::Variable>();
    t->setName("t");
    t->setUnits("millisecond");
    // Note: time is our integration base variable so is not initialised

    libcellml::VariablePtr V = std::make_shared<libcellml::Variable>();
    V->setName("V");
    V->setUnits("millivolt");
    V->setInitialValue(0.0);

    libcellml::VariablePtr alpha_y = std::make_shared<libcellml::Variable>();
    alpha_y->setName("alpha_y");
    alpha_y->setUnits("per_millisecond");
    alpha_y->setInitialValue(1.0);

    libcellml::VariablePtr beta_y = std::make_shared<libcellml::Variable>();
    beta_y->setName("beta_y");
    beta_y->setUnits("per_millisecond");
    beta_y->setInitialValue(2.0);

    libcellml::VariablePtr y = std::make_shared<libcellml::Variable>();
    y->setName("y");
    y->setUnits("dimensionless");
    y->setInitialValue(1.0);

    libcellml::VariablePtr E_y = std::make_shared<libcellml::Variable>();
    E_y->setName("E_y");
    E_y->setUnits("millivolt");
    E_y->setInitialValue(-85.0);

    libcellml::VariablePtr i_y = std::make_shared<libcellml::Variable>();
    i_y->setName("i_y");
    i_y->setUnits("microA_per_cm2");
    // Note that no initial value is needed for this variable as its value
    // is defined by equation2

    libcellml::VariablePtr g_y = std::make_shared<libcellml::Variable>();
    g_y->setName("g_y");
    g_y->setUnits("milliS_per_cm2");
    g_y->setInitialValue(36.0);

    libcellml::VariablePtr gamma = std::make_shared<libcellml::Variable>();
    gamma->setName("gamma");
    gamma->setUnits("dimensionless");
    gamma->setInitialValue(4.0);

    //  3.c Adding the variables to the component.  Note that Variables are
    //      added by their pointer (cf. their name)
    component->addVariable(t);
    component->addVariable(V);
    component->addVariable(E_y);
    component->addVariable(gamma);
    component->addVariable(i_y);
    component->addVariable(g_y);
    component->addVariable(alpha_y);
    component->addVariable(beta_y);
    component->addVariable(y);

    //  4.a Defining the units of millisecond, millivolt, per_millisecond,
    //      microA_per_cm2, and milliS_per_cm2. Note that the dimensionless
    //      units are part of those built-in already, so do not need to be
    //      defined here.
    libcellml::UnitsPtr ms = std::make_shared<libcellml::Units>();
    ms->setName("millisecond");
    ms->addUnit("second", "milli");

    libcellml::UnitsPtr mV = std::make_shared<libcellml::Units>();
    mV->setName("millivolt");
    mV->addUnit("volt", "milli");

    libcellml::UnitsPtr per_ms = std::make_shared<libcellml::Units>();
    per_ms->setName("per_millisecond");
    per_ms->addUnit("millisecond", -1.0);

    libcellml::UnitsPtr microA_per_cm2 = std::make_shared<libcellml::Units>();
    microA_per_cm2->setName("microA_per_cm2");
    microA_per_cm2->addUnit("ampere", "micro");
    microA_per_cm2->addUnit("metre", "centi", -2.0);

    libcellml::UnitsPtr mS_per_cm2 = std::make_shared<libcellml::Units>();
    mS_per_cm2->setName("milliS_per_cm2");
    mS_per_cm2->addUnit("siemens", "milli");
    mS_per_cm2->addUnit("metre", "centi", -2.0);

    //  4.b Add these units into the model
    model->addUnits(ms);
    model->addUnits(mV);
    model->addUnits(per_ms);
    model->addUnits(microA_per_cm2);
    model->addUnits(mS_per_cm2);

    //  4.c Validate the final arrangement.  No errors are expected at this stage.
    libcellml::Validator validator;
    validator.validateModel(model);
    printErrors(validator);

    //  5.a   Create a Generator instance.  By default the options set in the
    //        generator constructor are:
    //          - profile() return "C" (cf "PYTHON")
    //          - modelType() returns "ODE"

    libcellml::Generator generator;
    generator.processModel(model);

    //  5.b Check whether the generator has encountered any errors
    printErrors(generator);

    EXPECT_EQ(size_t(0), generator.errorCount());
}
