#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP
#ifndef XERCES_STRINGS_HPP_INCLUDED 
#define XERCES_STRINGS_HPP_INCLUDED



#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>


#include <xercesc/util/XMLString.hpp>

#include <string>
#include <stdexcept>
#include <string>
#include <stdexcept>
#include "dcLabel.h" 
#include "AmRunnable.h"
#include "dcRemoteAccessInstruction.h"
#include "dcExecutionCyclesConstantInstruction.h"
#include "dcExecutionCyclesDeviationInstruction.h"
#include "dcGroupInstruction.h"
#include "AmTask.h"
#include "dcActEvent.h"
#include "dcCoreType.h"
#include "dcCore.h"
#include "dcMicrocontroller.h"
#include "dcQuartz.h"
#include "dcPeriodicEvent.h"
#include "dcSporadicEvent.h"
#include "dcTag.h"
#include "dcAperiodicEvent.h"
#include "dcDeterministicIrregularEvent.h"
#include "dcRunnableExecutionTime.h"
#include "dcFixedRunnableExecTime.h"
#include "dcVariableRunnableExecTime.h"
#include "AmApplication.h"

// Error codes
enum {
	ERROR_ARGS = 1, 
	ERROR_XERCES_INIT,
	ERROR_PARSE,
	ERROR_EMPTY_DOCUMENT
};

using namespace DCApplication;
using namespace std;
using namespace xercesc;

class dcAmaltheaParser{

public:
	dcAmaltheaParser();
	~dcAmaltheaParser();

	void ParseAmaltheaFile(string& FileName, AmApplication* MyAmApplication);
	string GetAttributeAsString(DOMElement* MyElement,XMLCh* MyAttr);
	void ParseAmaltheaFileLabels(DOMNodeList* const children, AmApplication* MyAmApplication);

	void ParseAmaltheaTags(DOMNodeList* const children , AmApplication* MyAmApplication);
	void FillPeriodicEventType(DOMElement* currentElementLev2, dcPeriodicEvent *MyPeriodicEvent);
	void FillSporadicEventType(DOMElement* currentElementLev2, dcSporadicEvent *MySporadicEvent);
	void FillAperiodicEventType(DOMElement* currentElementLev3, dcAperiodicEvent *MyAperioidicEvent);
	void FillDeterministicIrregularEventType(DOMElement* currentElementLev3, dcDeterministicIrregularEvent *MyDeterministicIrregularEvent);
	void ParseAmaltheaFileStimuli(DOMNodeList* const children , AmApplication* MyAmApplication);
	void FillInterProcessActivation(DOMElement* currentElementLev4, AmTask* MyTask, AmApplication* MyAmApplication);

	void ParseAmaltheaFileRunnable(DOMNodeList* const children , AmApplication* MyAmApplication);
	void ParseAmaltheaFileTasks(DOMNodeList* const children , AmApplication* MyAmApplication);
	void ParseAmaltheaFileHWModel(DOMNodeList* const children , AmApplication* MyAmApplication);
	int ParseAmaltheaFileHWModelForCoresNo(DOMNodeList* const children , AmApplication* MyAmApplication);
	int	ParseAmaltheaFileRunnableForNo(DOMNodeList* const children , AmApplication* MyAmApplication);

	void FillExecutionCyclesDeviationInstruction(DOMElement* currentElementLev2, dcExecutionCyclesDeviationInstruction *MyExecutionCyclesDeviationInstruction);
	void FillRemoteAccessInstruction(DOMElement* currentElementLev2,dcRemoteAccessInstruction *MyRemoteAccessInstruction,AmApplication *MyAmApplication);
	void FillExecutionCyclesConstantInstruction(DOMElement* currentElementLev2,dcExecutionCyclesConstantInstruction *MyExecutionCyclesConstantInstruction);
	void AnalyseGroup(DOMElement* currentElementLev2,AmApplication *MyAmApplication,AmRunnable *MyRunnable);

	DOMNodeList* GetElementWithTagswModel(DOMNode* root);
	DOMNodeList* GetElementWithTaghwModel(DOMNode* root);
	DOMNodeList* GetElementWithTagStimuliModel(DOMNode* root);

private:
	xercesc::XercesDOMParser *m_Parser;

	// Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

	XMLCh* TAG_root;

	XMLCh* TAG_labels;
	XMLCh* TAG_runnables;
	XMLCh* TAG_remoteAccesses;
	XMLCh* TAG_deviation;
	XMLCh* TAG_lowerBound;
	XMLCh* TAG_upperBound;
	XMLCh* TAG_distribution;
	XMLCh* TAG_mean;
	XMLCh* TAG_sd;

	XMLCh* TAG_tasks;
	XMLCh* TAG_deadline;
	XMLCh* TAG_callGraph;
	XMLCh* TAG_graphEntries;
	XMLCh* TAG_calls;
	XMLCh* TAG_swModel;
	XMLCh* TAG_runnableItems;

	XMLCh* TAG_size;
	XMLCh* TAG_items;
	XMLCh* TAG_runnableItem;
	XMLCh* TAG_tags;


	XMLCh* TAG_stimuliModel;
	XMLCh* TAG_stimulusDeviation;
	XMLCh* TAG_stimuli;
	XMLCh* TAG_offset;
	XMLCh* TAG_recurrence;
	XMLCh* TAG_hwModel;
	XMLCh* TAG_coreTypes;
	XMLCh* TAG_system;
	XMLCh* TAG_ecus;
	XMLCh* TAG_quartzes;
	XMLCh* TAG_microcontrollers;
	XMLCh* TAG_cores;
	XMLCh* TAG_prescaler;
	XMLCh* TAG_stimuli_stimuliModel;
	XMLCh* TAG_hw_hwModel;
	XMLCh* TAG_sw_swModel;
	XMLCh* TAG_stimulus;
	XMLCh* TAG_entries;
	XMLCh* TAG_customProperties;
	XMLCh* TAG_values;
	XMLCh* TAG_value;


	XMLCh* ATTR_name;
	XMLCh* ATTR_xsi_type;
	XMLCh* ATTR_data;
	XMLCh* ATTR_value;
	XMLCh* ATTR_pRemainPromille;
	XMLCh* ATTR_tags;
	XMLCh* ATTR_numberBits;
	XMLCh* ATTR_access;

	XMLCh* ATTR_priority;
	XMLCh* ATTR_multipleTaskActivationLimit;
	XMLCh* ATTR_unit;
	XMLCh* ATTR_runnable;
	XMLCh* ATTR_preemption;
	XMLCh* ATTR_xmi_id;
	XMLCh* ATTR_stimuli;
	XMLCh* ATTR_instructionsPerCycle;
	XMLCh* ATTR_frequency;
	XMLCh* ATTR_coreType;
	XMLCh* ATTR_quartz;
	XMLCh* ATTR_stimulus;
	XMLCh* ATTR_href;
	XMLCh* ATTR_kappa;
	XMLCh* ATTR_lambda;
	XMLCh* ATTR_probability;
	XMLCh* ATTR_tagName;
	XMLCh* ATTR_key;
	
	int TaskCounter; //counter for tasks ID
	int RunCounter; //counter for runnable ID
};


#endif
#endif