#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <random>
#include <time.h> 
#include <stdlib.h>

#include "dcAmaltheaParser.h"

using namespace xercesc;
using namespace DCApplication;
using namespace std;

/** 
*  Constructor initializes xerces-C libraries.
*  The XML tags and attributes which we seek are defined.
*  The xerces-C DOM parser infrastructure is initialized.
*/

dcAmaltheaParser::dcAmaltheaParser()
{

	try
	{
		XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
	}
	catch( XMLException& e )
	{
		char* message = XMLString::transcode( e.getMessage() );
		cerr << "XML toolkit initialization error: " << message << endl;
		XMLString::release( &message );
		// throw exception here to return ERROR_XERCES_INIT
	}

	// Tags and attributes used in XML file.
	// Can't call transcode till after Xerces Initialize()
	TAG_root        = XMLString::transcode("sw:SWModel");


	TAG_labels= XMLString::transcode("labels");
	TAG_runnables= XMLString::transcode("runnables");
	TAG_remoteAccesses= XMLString::transcode("remoteAccesses");
	TAG_deviation= XMLString::transcode("deviation");
	TAG_lowerBound= XMLString::transcode("lowerBound");
	TAG_upperBound= XMLString::transcode("upperBound");
	TAG_distribution= XMLString::transcode("distribution");
	TAG_mean= XMLString::transcode("mean");
	TAG_size= XMLString::transcode("size");
	TAG_sd=  XMLString::transcode("sd");
	TAG_tasks=  XMLString::transcode("tasks");
	TAG_deadline=  XMLString::transcode("deadline");
	TAG_callGraph=  XMLString::transcode("callGraph");
	TAG_graphEntries=  XMLString::transcode("graphEntries");
	TAG_calls=  XMLString::transcode("calls");
	TAG_swModel=  XMLString::transcode("swModel");
	TAG_runnableItems=  XMLString::transcode("runnableItems");
	TAG_stimuliModel=  XMLString::transcode("stimuliModel");
	TAG_stimuli_stimuliModel=  XMLString::transcode("stimuli:StimuliModel");
	TAG_stimulusDeviation = XMLString::transcode("stimulusDeviation");


	TAG_stimuli=  XMLString::transcode("stimuli");
	TAG_offset=  XMLString::transcode("offset");
	TAG_recurrence=  XMLString::transcode("recurrence");
	TAG_hwModel=  XMLString::transcode("hwModel");
	TAG_coreTypes=  XMLString::transcode("coreTypes");
	TAG_system=  XMLString::transcode("system");
	TAG_ecus=  XMLString::transcode("ecus");
	TAG_quartzes=  XMLString::transcode("quartzes");
	TAG_microcontrollers=  XMLString::transcode("microcontrollers");
	TAG_cores=  XMLString::transcode("cores");
	TAG_prescaler=  XMLString::transcode("prescaler");
	TAG_hw_hwModel=  XMLString::transcode("hw:HWModel"); 
	TAG_sw_swModel=  XMLString::transcode("sw:SWModel");
	TAG_items=  XMLString::transcode("items"); 
	TAG_runnableItem=  XMLString::transcode("runnableItem"); 
	TAG_stimulus=  XMLString::transcode("stimulus");
	TAG_entries = XMLString::transcode("entries");
	TAG_tags = XMLString::transcode("tags");
	TAG_customProperties = XMLString::transcode("customProperties");
	TAG_value = XMLString::transcode("value");
	TAG_values = XMLString::transcode("values");


	ATTR_name= XMLString::transcode("name");
	ATTR_xsi_type= XMLString::transcode("xsi:type");
	ATTR_data= XMLString::transcode("data");
	ATTR_value= XMLString::transcode("value");
	ATTR_pRemainPromille= XMLString::transcode("pRemainPromille");
	ATTR_tags= XMLString::transcode("tags");
	ATTR_numberBits= XMLString::transcode("numberBits");
	ATTR_access= XMLString::transcode("access");
	ATTR_priority= XMLString::transcode("priority");
	ATTR_multipleTaskActivationLimit= XMLString::transcode("multipleTaskActivationLimit");
	ATTR_unit= XMLString::transcode("unit");
	ATTR_runnable= XMLString::transcode("runnable");
	ATTR_preemption=XMLString::transcode("preemption");
	ATTR_xmi_id=XMLString::transcode("xmi:id");
	ATTR_stimuli=XMLString::transcode("stimuli");

	ATTR_instructionsPerCycle=XMLString::transcode("instructionsPerCycle");
	ATTR_frequency=XMLString::transcode("frequency");
	ATTR_coreType=XMLString::transcode("coreType");
	ATTR_quartz=XMLString::transcode("quartz");
	ATTR_stimulus=XMLString::transcode("stimulus");
	ATTR_href=XMLString::transcode("href");
	ATTR_kappa=XMLString::transcode("kappa");
	ATTR_lambda=XMLString::transcode("lambda");
	ATTR_probability = XMLString::transcode("probability");
	ATTR_tagName = XMLString::transcode("tagName");
	ATTR_key= XMLString::transcode("key");

	TaskCounter = 0;
	RunCounter = 0;


	m_Parser = new XercesDOMParser;
}

/*#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif*/

/**
*  Class destructor frees memory used to hold the XML tag and 
*  attribute definitions. It als terminates use of the xerces-C
*  framework.
*/

dcAmaltheaParser::~dcAmaltheaParser()
{
	// Free memory

	delete m_Parser;

	try
	{
		XMLString::release( &TAG_labels );
		XMLString::release( &TAG_runnables );
		XMLString::release( &TAG_remoteAccesses );
		XMLString::release( &TAG_deviation );
		XMLString::release( &TAG_lowerBound );
		XMLString::release( &TAG_upperBound );
		XMLString::release( &TAG_distribution );
		XMLString::release( &TAG_mean );
		XMLString::release( &TAG_sd );
		XMLString::release( &TAG_runnableItems );
		XMLString::release( &TAG_size );
		XMLString::release( &TAG_stimuliModel );
		XMLString::release( &TAG_stimuli );
		XMLString::release( &TAG_offset );
		XMLString::release( &TAG_recurrence );
		XMLString::release( &TAG_tasks );
		XMLString::release( &TAG_deadline );
		XMLString::release( &TAG_callGraph );
		XMLString::release( &TAG_graphEntries );
		XMLString::release( &TAG_calls );
		XMLString::release( &TAG_hwModel );
		XMLString::release( &TAG_swModel );
		XMLString::release( &TAG_coreTypes );
		XMLString::release( &TAG_system );
		XMLString::release( &TAG_ecus );
		XMLString::release( &TAG_quartzes );
		XMLString::release( &TAG_microcontrollers );
		XMLString::release( &TAG_cores );
		XMLString::release( &TAG_prescaler );
		XMLString::release( &TAG_hw_hwModel );
		XMLString::release( &TAG_sw_swModel );
		XMLString::release( &TAG_stimuli_stimuliModel );
		XMLString::release( &TAG_items );
		XMLString::release( &TAG_runnableItem );
		XMLString::release( &TAG_stimulus );
		XMLString::release( &TAG_value );
		XMLString::release( &TAG_values );
		XMLString::release( &TAG_customProperties );


		XMLString::release( &ATTR_name );
		XMLString::release( &ATTR_xsi_type );
		XMLString::release( &ATTR_data );
		XMLString::release( &ATTR_value );
		XMLString::release( &ATTR_pRemainPromille );
		XMLString::release( &ATTR_tags );
		XMLString::release( &ATTR_numberBits );
		XMLString::release( &ATTR_access );
		XMLString::release( &ATTR_priority );
		XMLString::release( &ATTR_multipleTaskActivationLimit );
		XMLString::release( &ATTR_unit );
		XMLString::release( &ATTR_runnable );
		XMLString::release( &ATTR_preemption );
		XMLString::release( &ATTR_xmi_id );
		XMLString::release( &ATTR_stimuli );
		XMLString::release( &ATTR_instructionsPerCycle );
		XMLString::release( &ATTR_frequency );
		XMLString::release( &ATTR_coreType );
		XMLString::release( &ATTR_quartz );
		XMLString::release( &ATTR_stimulus );
		XMLString::release( &ATTR_href );
		XMLString::release(&ATTR_kappa);
		XMLString::release(&ATTR_lambda);
		XMLString::release(&ATTR_probability);
		XMLString::release(&ATTR_tagName);
		XMLString::release(&ATTR_key);
	}
	catch( ... )
	{
		cerr << "Unknown exception encountered in TagNamesdtor" << endl;
	}

	// Terminate Xerces

	try
	{
		XMLPlatformUtils::Terminate();  // Terminate after release of memory
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		cerr << "XML ttolkit teardown error: " << message << endl;
		XMLString::release( &message );
	}
}

string dcAmaltheaParser::GetAttributeAsString(DOMElement* MyElement,XMLCh* MyAttr) {
	const XMLCh* xmlch_string = MyElement->getAttribute(MyAttr);
	return XMLString::transcode(xmlch_string);
}

DOMNodeList* dcAmaltheaParser::GetElementWithTagswModel(DOMNode* root) {

	DOMNodeList* result=NULL;
	if( root->getNodeType() &&  // true is not NULL
		root->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
	{
		DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( root );
		if( XMLString::equals(currentElement->getTagName(), TAG_sw_swModel) || XMLString::equals(currentElement->getTagName(), TAG_swModel) ) { 
			result = currentElement->getChildNodes();
			return result;
		}
	}


	DOMNodeList* children=root->getChildNodes();
	int nodeCount = children->getLength();
	

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
			if( XMLString::equals(currentElement->getTagName(), TAG_sw_swModel) || XMLString::equals(currentElement->getTagName(), TAG_swModel) ) { 
				result = currentElement->getChildNodes();
				return result;
			}
		}
	}
	return result;
}

DOMNodeList* dcAmaltheaParser::GetElementWithTaghwModel(DOMNode* root) {

	DOMNodeList* result=NULL;
	if( root->getNodeType() &&  // true is not NULL
		root->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
	{
		DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( root );
		if( XMLString::equals(currentElement->getTagName(), TAG_hw_hwModel) || XMLString::equals(currentElement->getTagName(), TAG_hwModel)) { 
			result = currentElement->getChildNodes();
			return result;
		}
	}


	DOMNodeList* children=root->getChildNodes();
	int nodeCount = children->getLength();



	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
			if( XMLString::equals(currentElement->getTagName(), TAG_hw_hwModel) || XMLString::equals(currentElement->getTagName(), TAG_hwModel)) { 
				result = currentElement->getChildNodes();
				return result;
			}


		}
	}
	return result;
}

DOMNodeList* dcAmaltheaParser::GetElementWithTagStimuliModel(DOMNode* root) {

	DOMNodeList* result=NULL;
	if( root->getNodeType() &&  // true is not NULL
		root->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
	{
		DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( root );
		if( XMLString::equals(currentElement->getTagName(), TAG_stimuli_stimuliModel) || XMLString::equals(currentElement->getTagName(), TAG_stimuliModel)) { 
			result = currentElement->getChildNodes();
			return result;
		}
	}


	DOMNodeList* children=root->getChildNodes();
	int nodeCount = children->getLength();



	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
			if( XMLString::equals(currentElement->getTagName(), TAG_stimuli_stimuliModel) || XMLString::equals(currentElement->getTagName(), TAG_stimuliModel)) { 
				result = currentElement->getChildNodes();
				return result;
			}


		}
	}
	return result;
}

int dcAmaltheaParser::ParseAmaltheaFileHWModelForCoresNo(DOMNodeList* const children , AmApplication* MyAmApplication) {

	if (children==NULL) {
		return -1; // no hw model
	}

	int result=0;
	int nodeCount = children->getLength();


	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );

			if( XMLString::equals(currentElement->getTagName(), TAG_system))
			{
				DOMNodeList* childrenLev2 = currentElement->getChildNodes();
				const  XMLSize_t nodeCountLev2 = childrenLev2->getLength();
				for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
				{
					DOMNode* currentNodeLev2 = childrenLev2->item(xxLev2);
					if( currentNodeLev2->getNodeType() &&  // true is not NULL
						currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
						if( XMLString::equals(currentElementLev2->getTagName(), TAG_ecus))
						{
							const XMLCh* xmlch_stringLev2 = currentElementLev2->getAttribute(ATTR_name);
							string strSize = XMLString::transcode(xmlch_stringLev2);


							DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
							const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
							for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
							{
								DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
								if( currentNodeLev3->getNodeType() &&  // true is not NULL
									currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
								{
									DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
									if( XMLString::equals(currentElementLev3->getTagName(), TAG_microcontrollers))
									{
										const XMLCh* xmlch_Name = currentElementLev3->getAttribute(ATTR_name);
										string strName = XMLString::transcode(xmlch_Name);




										DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
										const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
										for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
										{
											DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
											if( currentNodeLev4->getNodeType() &&  // true is not NULL
												currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
											{
												DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );

												if( XMLString::equals(currentElementLev4->getTagName(), TAG_cores))
												{
													result++;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int	dcAmaltheaParser::ParseAmaltheaFileRunnableForNo(DOMNodeList* const children , AmApplication* MyAmApplication) {
	int result=0;
	int nodeCount = children->getLength();

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );


			if( XMLString::equals(currentElement->getTagName(), TAG_runnables))
			{
				result++;
			}
		}
	}
	return result;
}

void dcAmaltheaParser::ParseAmaltheaFileHWModel(DOMNodeList* const children , AmApplication* MyAmApplication) {

	if (children==NULL) {
		return; // no hw model
	}

	int nodeCount = children->getLength();


	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );

			if( XMLString::equals(currentElement->getTagName(), TAG_coreTypes))
			{
				dcCoreType* MyCoreType = new dcCoreType(GetAttributeAsString(currentElement,ATTR_name));
				MyCoreType->SetID(GetAttributeAsString(currentElement,ATTR_xmi_id));
				MyCoreType->SetInstructionsPerCycle(atoi(GetAttributeAsString(currentElement,ATTR_instructionsPerCycle).c_str()));
				MyAmApplication->AddCoreType(MyCoreType,MyCoreType->GetID());
			}
			else if( XMLString::equals(currentElement->getTagName(), TAG_system))
			{
				DOMNodeList* childrenLev2 = currentElement->getChildNodes();
				const  XMLSize_t nodeCountLev2 = childrenLev2->getLength();
				for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
				{
					DOMNode* currentNodeLev2 = childrenLev2->item(xxLev2);
					if( currentNodeLev2->getNodeType() &&  // true is not NULL
						currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
						if( XMLString::equals(currentElementLev2->getTagName(), TAG_ecus))
						{
							const XMLCh* xmlch_stringLev2 = currentElementLev2->getAttribute(ATTR_name);
							string strSize = XMLString::transcode(xmlch_stringLev2);


							DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
							const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
							for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
							{
								DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
								if( currentNodeLev3->getNodeType() &&  // true is not NULL
									currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
								{
									DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
									if( XMLString::equals(currentElementLev3->getTagName(), TAG_quartzes))
									{
										dcQuartz* MyQuartz=new dcQuartz(GetAttributeAsString(currentElementLev3,ATTR_name));
										MyQuartz->SetID(GetAttributeAsString(currentElementLev3,ATTR_xmi_id));
										MyQuartz->SetFrequency(atoi(GetAttributeAsString(currentElementLev3,ATTR_frequency).c_str()));
										MyAmApplication->AddQuartz(MyQuartz,MyQuartz->GetID());

									}
									else if( XMLString::equals(currentElementLev3->getTagName(), TAG_microcontrollers))
									{
										const XMLCh* xmlch_Name = currentElementLev3->getAttribute(ATTR_name);
										string strName = XMLString::transcode(xmlch_Name);




										DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
										const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
										for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
										{
											DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
											if( currentNodeLev4->getNodeType() &&  // true is not NULL
												currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
											{
												DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );

												if( XMLString::equals(currentElementLev4->getTagName(), TAG_cores))
												{
													dcCore* MyCore = new dcCore(GetAttributeAsString(currentElementLev4,ATTR_name));
													MyCore->SetCoreType(MyAmApplication->GetCoreType(GetAttributeAsString(currentElementLev4,ATTR_coreType)));


													DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
													const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
													for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
													{
														DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
														if( currentNodeLev5->getNodeType() &&  // true is not NULL
															currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
														{
															DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
															if( XMLString::equals(currentElementLev5->getTagName(), TAG_prescaler))
															{
																MyCore->SetName(GetAttributeAsString(currentElementLev5,ATTR_name));
																MyCore->SetID(GetAttributeAsString(currentElementLev5,ATTR_xmi_id));
																MyCore->SetQuartz(MyAmApplication->GetQuartz(GetAttributeAsString(currentElementLev5,ATTR_quartz)));



															}
														}
													}

													MyAmApplication->AddCore(MyCore,MyCore->GetID());
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void dcAmaltheaParser::FillPeriodicEventType(DOMElement* currentElementLev2, dcPeriodicEvent *MyPeriodicEvent){
	MyPeriodicEvent->SetID(GetAttributeAsString(currentElementLev2,ATTR_xmi_id));
	MyPeriodicEvent->SetType(GetAttributeAsString(currentElementLev2,ATTR_xsi_type));
	DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
	const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
	for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
	{
		DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
		if( currentNodeLev3->getNodeType() &&  // true is not NULL
			currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
			if( XMLString::equals(currentElementLev3->getTagName(), TAG_offset))
			{
				string strValue = GetAttributeAsString(currentElementLev3,ATTR_value);
				string strUnit = GetAttributeAsString(currentElementLev3,ATTR_unit);
				if(strValue=="") {
					strValue="0";
				}
				if(strUnit=="") {
					strUnit="ms";
				}

				MyPeriodicEvent->SetOffset(pair<int,string>(atoi(strValue.c_str()),strUnit));
			}else if( XMLString::equals(currentElementLev3->getTagName(), TAG_recurrence)){
				string strValue = GetAttributeAsString(currentElementLev3,ATTR_value);
				string strUnit = GetAttributeAsString(currentElementLev3,ATTR_unit);
				if(strValue=="") {
					strValue="0";
				}
				if(strUnit=="") {
					strUnit="ms";
				}
				MyPeriodicEvent->SetRecurrence(pair<int,string>(atoi(strValue.c_str()),strUnit));
			}
		}

	}
}

void dcAmaltheaParser::FillSporadicEventType(DOMElement* currentElementLev2, dcSporadicEvent *MySporadicEvent){
	MySporadicEvent->SetID(GetAttributeAsString(currentElementLev2,ATTR_xmi_id));
	MySporadicEvent->SetType(GetAttributeAsString(currentElementLev2,ATTR_xsi_type));

	DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
	const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

	for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
	{
		DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
		if( currentNodeLev3->getNodeType() &&  // true is not NULL
			currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
			if( XMLString::equals(currentElementLev3->getTagName(), TAG_stimulusDeviation)){
				DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
				const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
				for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
				{
					DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
					if( currentNodeLev4->getNodeType() &&  // true is not NULL
						currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
						if( XMLString::equals(currentElementLev4->getTagName(), TAG_upperBound))
						{
							MySporadicEvent->SetUpperBound(atoi(GetAttributeAsString(currentElementLev4,ATTR_value).c_str()));
						}else if( XMLString::equals(currentElementLev4->getTagName(), TAG_lowerBound))
						{
							MySporadicEvent->SetLowerBound(atoi(GetAttributeAsString(currentElementLev4,ATTR_value).c_str()));
						}else if( XMLString::equals(currentElementLev4->getTagName(), TAG_distribution))
						{
							MySporadicEvent->SetDistType(GetAttributeAsString(currentElementLev4,ATTR_xsi_type));

							if(MySporadicEvent->GetDistType() == "common:WeibullEstimators") {
								MySporadicEvent->SetRemainPromille(atof(GetAttributeAsString(currentElementLev4,ATTR_pRemainPromille).c_str()));
							}else if(MySporadicEvent->GetDistType() == "common:WeibullParameters"){
								MySporadicEvent->SetKappa(atof(GetAttributeAsString(currentElementLev4,ATTR_kappa).c_str()));
								MySporadicEvent->SetLambda(atof(GetAttributeAsString(currentElementLev4,ATTR_lambda).c_str()));
							}else if(MySporadicEvent->GetDistType() == "common:GaussDistribution"){
								DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
								const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
								for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
								{
									DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
									if( currentNodeLev5->getNodeType() &&  // true is not NULL
										currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
										if( XMLString::equals(currentElementLev5->getTagName(), TAG_mean))
										{
											MySporadicEvent->SetMean(atof(GetAttributeAsString(currentElementLev5,ATTR_value).c_str()));
										}
										else if( XMLString::equals(currentElementLev5->getTagName(), TAG_sd))
										{
											MySporadicEvent->SetSD(atof(GetAttributeAsString(currentElementLev5,ATTR_value).c_str()));
										}
									}
								}
							}
						}
					}
				}
			}

		}
	}



}

void dcAmaltheaParser::FillAperiodicEventType(DOMElement* currentElementLev3, dcAperiodicEvent* MyAperiodicEvent){
	DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
	const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
	for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
	{
		DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
		if( currentNodeLev4->getNodeType() &&  // true is not NULL
			currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
			if( XMLString::equals(currentElementLev4->getTagName(), TAG_value))
			{
				string strVal = GetAttributeAsString(currentElementLev4,ATTR_value);
				MyAperiodicEvent->SetVal(strVal);
			}

		}
	}
}

void dcAmaltheaParser::FillDeterministicIrregularEventType(DOMElement* currentElementLev3, dcDeterministicIrregularEvent* MyDeterministicIrregularEvent){
	DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
	const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
	for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
	{
		DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
		if( currentNodeLev4->getNodeType() &&  // true is not NULL
			currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
			if( XMLString::equals(currentElementLev4->getTagName(), TAG_value))
			{
				DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
				const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
				for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
				{
					DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
					if( currentNodeLev5->getNodeType() &&  // true is not NULL
						currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
						if( XMLString::equals(currentElementLev5->getTagName(), TAG_values))
						{
							MyDeterministicIrregularEvent->AddArrivalTimes(GetAttributeAsString(currentElementLev5,ATTR_value));
						}
					}
				}
			}

		}
	}
}

void dcAmaltheaParser::ParseAmaltheaFileStimuli(DOMNodeList* const currentElement , AmApplication* MyAmaltheaSystem) {
	if (currentElement==NULL) {
		return; // no hw model
	}
	const  XMLSize_t nodeCountLev2 = currentElement->getLength();
	for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
	{
		DOMNode* currentNodeLev2 = currentElement->item(xxLev2);
		if( currentNodeLev2->getNodeType() &&  // true is not NULL
			currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
			if( XMLString::equals(currentElementLev2->getTagName(), TAG_stimuli))
			{
				string strStimuliType = GetAttributeAsString(currentElementLev2,ATTR_xsi_type);

				if(strStimuliType == "stimuli:Periodic"){
					dcPeriodicEvent* MyPeriodicEvent = new dcPeriodicEvent(GetAttributeAsString(currentElementLev2,ATTR_name));
					FillPeriodicEventType(currentElementLev2, MyPeriodicEvent);

					MyAmaltheaSystem->AddActEvent(MyPeriodicEvent, MyPeriodicEvent->GetID());
					MyAmaltheaSystem->AddPeriodicEvent(MyPeriodicEvent);
					

				}else if(strStimuliType == "stimuli:Sporadic"){
					dcSporadicEvent* MySporadicEvent = new dcSporadicEvent(GetAttributeAsString(currentElementLev2,ATTR_name));
					FillSporadicEventType(currentElementLev2, MySporadicEvent);
					MyAmaltheaSystem->AddActEvent(MySporadicEvent, MySporadicEvent->GetID());

					MyAmaltheaSystem->AddSporadicEvent(MySporadicEvent);
				}else if(strStimuliType == "stimuli:CustomStimulus"){

					//create stimulus
					string strName = GetAttributeAsString(currentElementLev2,ATTR_name);
					string strID = GetAttributeAsString(currentElementLev2,ATTR_xmi_id);

					//get the type i.e. aperiodic or determinstic irregular
					DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
					const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

					for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
					{
						DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
						if( currentNodeLev3->getNodeType() &&  // true is not NULL
							currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
						{
							DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );

							if( XMLString::equals(currentElementLev3->getTagName(), TAG_customProperties)){
								string custType = GetAttributeAsString(currentElementLev3,ATTR_key);
								if(custType == "Aperiodic"){
									dcAperiodicEvent* MyAperiodicEvent = new dcAperiodicEvent(strName);
									MyAperiodicEvent->SetID(strID);
									MyAperiodicEvent->SetType(custType);
									FillAperiodicEventType(currentElementLev3,MyAperiodicEvent);
									MyAmaltheaSystem->AddActEvent(MyAperiodicEvent, MyAperiodicEvent->GetID());

									MyAmaltheaSystem->AddAperiodicEVent(MyAperiodicEvent);

								}else if(custType == "DeterministicIrregular"){
									dcDeterministicIrregularEvent* MyDeterministicIrregularEvent = new dcDeterministicIrregularEvent(strName);
									MyDeterministicIrregularEvent->SetID(strID);
									MyDeterministicIrregularEvent->SetType(custType);
									FillDeterministicIrregularEventType(currentElementLev3, MyDeterministicIrregularEvent);
									MyAmaltheaSystem->AddActEvent(MyDeterministicIrregularEvent, MyDeterministicIrregularEvent->GetID());
									
									MyAmaltheaSystem->AddDeterministicIrregularEvent(MyDeterministicIrregularEvent);

								}else if(custType == "schedulingType"){
									
									DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
									const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
									for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
									{
										DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
										if( currentNodeLev4->getNodeType() &&  // true is not NULL
											currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
										{
											DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
											if( XMLString::equals(currentElementLev4->getTagName(), TAG_value))
											{
												string strVal = GetAttributeAsString(currentElementLev4,ATTR_value);
												if(strVal =="sporadic"){
													dcSporadicEvent* MySporadicEvent = new dcSporadicEvent(strName);
													MySporadicEvent->SetID(strID);
													MySporadicEvent->SetType(custType);
													MyAmaltheaSystem->AddActEvent(MySporadicEvent, MySporadicEvent->GetID());
													
													MyAmaltheaSystem->AddSporadicEvent(MySporadicEvent);

												}
												
											}

										}
									}
								}
							}
						}
					}


				}else{
					dcActEvent* MyStimulus=new dcActEvent(GetAttributeAsString(currentElementLev2,ATTR_name));
					MyStimulus->SetID(GetAttributeAsString(currentElementLev2,ATTR_xmi_id));
					MyStimulus->SetType(strStimuliType);
					if(MyStimulus->GetID()!="") {
						MyAmaltheaSystem->AddActEvent(MyStimulus,MyStimulus->GetID());
					}
					else {
						MyAmaltheaSystem->AddActEvent(MyStimulus);
					}
				}
			}
		}
	}

}

void dcAmaltheaParser::FillRemoteAccessInstruction(DOMElement* currentElementLev2,dcRemoteAccessInstruction *MyRemoteAccessInstruction,AmApplication *MyAmApplication) {
	MyRemoteAccessInstruction->SetLabel(MyAmApplication->GetLabel(GetAttributeAsString(currentElementLev2,ATTR_data)));

	string strAccess = GetAttributeAsString(currentElementLev2,ATTR_access);
	if(strAccess=="write") {
		MyRemoteAccessInstruction->SetWrite(true);
	}
	else {
		MyRemoteAccessInstruction->SetWrite(false);
	}

}

void dcAmaltheaParser::FillExecutionCyclesConstantInstruction(DOMElement* currentElementLev2,dcExecutionCyclesConstantInstruction *MyExecutionCyclesConstantInstruction) {
	MyExecutionCyclesConstantInstruction->SetValue(atoi(GetAttributeAsString(currentElementLev2,ATTR_value).c_str()));
}

void dcAmaltheaParser::AnalyseGroup(DOMElement* currentElementLev2,AmApplication *MyAmApplication,AmRunnable *MyRunnable){
	DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
	const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
	for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
	{
		DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
		if( currentNodeLev3->getNodeType() &&  // true is not NULL
			currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
			if( XMLString::equals(currentElementLev3->getTagName(), TAG_items))
			{

				DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
				const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
				for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
				{
					DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
					if( currentNodeLev4->getNodeType() &&  // true is not NULL
						currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
						if( XMLString::equals(currentElementLev4->getTagName(), TAG_runnableItem))
						{
							string strInstructionType = GetAttributeAsString(currentElementLev4,ATTR_xsi_type);

							if(strInstructionType=="sw:LabelAccess") {
								dcRemoteAccessInstruction* MyRemoteAccessInstruction= new dcRemoteAccessInstruction(strInstructionType);
								FillRemoteAccessInstruction(currentElementLev4,MyRemoteAccessInstruction,MyAmApplication);
								MyRunnable->AddInstruction(MyRemoteAccessInstruction);
							}
							else if(strInstructionType=="sw:InstructionsDeviation") {
								dcExecutionCyclesDeviationInstruction* MyExecutionCyclesDeviationInstruction = new dcExecutionCyclesDeviationInstruction(strInstructionType);
								FillExecutionCyclesDeviationInstruction(currentElementLev4, MyExecutionCyclesDeviationInstruction);
								MyRunnable->AddInstruction(MyExecutionCyclesDeviationInstruction);

							}
							else if(strInstructionType=="sw:InstructionsConstant") {
								dcExecutionCyclesConstantInstruction* MyExecutionCyclesConstantInstruction = new dcExecutionCyclesConstantInstruction(strInstructionType);
								FillExecutionCyclesConstantInstruction(currentElementLev4,MyExecutionCyclesConstantInstruction);
								MyRunnable->AddInstruction(MyExecutionCyclesConstantInstruction);
							}
							else if(strInstructionType=="sw:Group") {
								AnalyseGroup(currentElementLev4,MyAmApplication,MyRunnable);
							}
							else {
								cerr<<"Not recognised instruction: " << strInstructionType << endl;

							}


						}

					}
				}
			}
		}
	}
}

void dcAmaltheaParser::FillExecutionCyclesDeviationInstruction(DOMElement* currentElementLev2, dcExecutionCyclesDeviationInstruction *MyExecutionCyclesDeviationInstruction) {

	DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
	const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
	for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
	{
		DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
		if( currentNodeLev3->getNodeType() &&  // true is not NULL
			currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
			if( XMLString::equals(currentElementLev3->getTagName(), TAG_deviation))
			{


				DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
				const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
				for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
				{
					DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
					if( currentNodeLev4->getNodeType() &&  // true is not NULL
						currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
						if( XMLString::equals(currentElementLev4->getTagName(), TAG_upperBound))
						{
							MyExecutionCyclesDeviationInstruction->SetUpperBound(atoi(GetAttributeAsString(currentElementLev4,ATTR_value).c_str()));
						}
						else if( XMLString::equals(currentElementLev4->getTagName(), TAG_lowerBound))
						{
							MyExecutionCyclesDeviationInstruction->SetLowerBound(atoi(GetAttributeAsString(currentElementLev4,ATTR_value).c_str()));
						}
						else if( XMLString::equals(currentElementLev4->getTagName(), TAG_distribution))
						{
							MyExecutionCyclesDeviationInstruction->SetType(GetAttributeAsString(currentElementLev4,ATTR_xsi_type));

							if(MyExecutionCyclesDeviationInstruction->GetType()=="common:WeibullEstimators") {
								MyExecutionCyclesDeviationInstruction->SetRemainPromille(atof(GetAttributeAsString(currentElementLev4,ATTR_pRemainPromille).c_str()));
							}

							DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
							const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
							for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
							{
								DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
								if( currentNodeLev5->getNodeType() &&  // true is not NULL
									currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
								{
									DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
									if( XMLString::equals(currentElementLev5->getTagName(), TAG_mean))
									{
										MyExecutionCyclesDeviationInstruction->SetMean(atof(GetAttributeAsString(currentElementLev5,ATTR_value).c_str()));
									}
									else if( XMLString::equals(currentElementLev5->getTagName(), TAG_sd))
									{
										MyExecutionCyclesDeviationInstruction->SetSD(atof(GetAttributeAsString(currentElementLev5,ATTR_value).c_str()));
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void dcAmaltheaParser::ParseAmaltheaFileRunnable(DOMNodeList* const children , AmApplication* MyAmApplication) {
	int nodeCount = children->getLength();

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );


			if( XMLString::equals(currentElement->getTagName(), TAG_runnables))
			{
				AmRunnable *MyRunnable = new AmRunnable(GetAttributeAsString(currentElement,ATTR_name));
				string ID = GetAttributeAsString(currentElement,ATTR_xmi_id);
				MyRunnable->SetID(ID);

				string strTag = GetAttributeAsString(currentElement,ATTR_tags);
				if(strTag != ""){
					dcTag* tag = MyAmApplication->GetTag(strTag);
					MyRunnable->SetTags(tag);
				}

				MyRunnable->SetRunnableID(RunCounter);
				RunCounter = RunCounter + 1;

				DOMNodeList* childrenLev2 = currentElement->getChildNodes();
				const  XMLSize_t nodeCountLev2 = childrenLev2->getLength();
				for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
				{
					DOMNode* currentNodeLev2 = childrenLev2->item(xxLev2);
					if( currentNodeLev2->getNodeType() &&  // true is not NULL
						currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
						if( XMLString::equals(currentElementLev2->getTagName(), TAG_size))
						{
							MyRunnable->SetSize(atoi(GetAttributeAsString(currentElementLev2,ATTR_numberBits).c_str()));

						}
						/*else if(XMLString::equals(currentElementLev2->getTagName(), TAG_deadline)){
							string strValue = GetAttributeAsString(currentElementLev2,ATTR_value);
							string strUnit = GetAttributeAsString(currentElementLev2,ATTR_unit);

							MyRunnable->SetDeadline(pair<int,string>(atoi(strValue.c_str()),strUnit));
						
						}*/
						else if(XMLString::equals(currentElementLev2->getTagName(), TAG_customProperties)){
							string key = GetAttributeAsString(currentElementLev2, ATTR_key);
							if(key == "OrderedTaskReleased"){
								DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
								const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

								for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
								{
									DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
									if( currentNodeLev3->getNodeType() &&  // true is not NULL
										currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
										if( XMLString::equals(currentElementLev3->getTagName(), TAG_value)){
											string orderedTaskReleased = GetAttributeAsString(currentElementLev3,ATTR_value);
											if(orderedTaskReleased =="true"){
												MyRunnable->SetOrderedTaskReleased(1);
											}else{
												MyRunnable->SetOrderedTaskReleased(0);
											}
										}
									}
								}
							}else if(key == "ExecutionTimeFixed"){
								dcFixedRunnableExecTime* MyFixedRunnableExecTime = new dcFixedRunnableExecTime(key);

								DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
								const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

								for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
								{
									DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
									if( currentNodeLev3->getNodeType() &&  // true is not NULL
										currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
										if( XMLString::equals(currentElementLev3->getTagName(), TAG_value)){
											string ReleasedTime = GetAttributeAsString(currentElementLev3,ATTR_value);
											MyFixedRunnableExecTime->SetExecutionTime(ReleasedTime);
											MyRunnable->SetRunnableExecutionTime(MyFixedRunnableExecTime);
										}
									}
								}
							}else if(key == "ExecutionTimeVariable"){
								dcVariableRunnableExecTime* MyVariableRunnableExecTime = new dcVariableRunnableExecTime(key);
								vector<string> temp; //temp buffer to store upper and lower bounds

								DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
								const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

								for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
								{
									DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
									if( currentNodeLev3->getNodeType() &&  // true is not NULL
										currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
										if( XMLString::equals(currentElementLev3->getTagName(), TAG_value)){
											DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
											const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
											for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
											{
												DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
												if( currentNodeLev4->getNodeType() &&  // true is not NULL
													currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
												{
													DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
													if( XMLString::equals(currentElementLev4->getTagName(), TAG_values))
													{
														string bound = GetAttributeAsString(currentElementLev4, ATTR_value);
														temp.push_back(bound);

														//set upper and lower bounds
														if(temp.size() == 2){
															MyVariableRunnableExecTime->SetLowerBound(temp.at(0));
															MyVariableRunnableExecTime->SetUpperBound(temp.at(1));

															//use rand() to set actual exec time
															//srand (time(NULL));
															srand ( (unsigned int)time(NULL) );
															int Actual = rand() % atoi(MyVariableRunnableExecTime->GetUpperBound().c_str()) + atoi(MyVariableRunnableExecTime->GetLowerBound().c_str());
															MyVariableRunnableExecTime->SetActualExecTime(to_string(Actual));
														}
													}
												}
											}
										}
									}
								}
							}else if(key == "ReleasedTasks"){
								DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
								const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();

								for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
								{
									DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
									if( currentNodeLev3->getNodeType() &&  // true is not NULL
										currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
										if( XMLString::equals(currentElementLev3->getTagName(), TAG_value)){
											DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
											const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
											for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
											{
												DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
												if( currentNodeLev4->getNodeType() &&  // true is not NULL
													currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
												{
													DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
													if( XMLString::equals(currentElementLev4->getTagName(), TAG_values))
													{
														string taskID = GetAttributeAsString(currentElementLev4, ATTR_value);
														//store taskId
														MyRunnable->AddReleasedTask(taskID);
													}
												}
											}
										}
									}
								}
							}
						}

						else if( XMLString::equals(currentElementLev2->getTagName(), TAG_runnableItems))
						{
							string strInstructionType = GetAttributeAsString(currentElementLev2,ATTR_xsi_type);

							if(strInstructionType=="sw:LabelAccess") {
								dcRemoteAccessInstruction* MyRemoteAccessInstruction= new dcRemoteAccessInstruction(strInstructionType);
								FillRemoteAccessInstruction(currentElementLev2,MyRemoteAccessInstruction,MyAmApplication);
								MyRunnable->AddInstruction(MyRemoteAccessInstruction);
							}
							else if(strInstructionType=="sw:InstructionsDeviation") {
								dcExecutionCyclesDeviationInstruction* MyExecutionCyclesDeviationInstruction = new dcExecutionCyclesDeviationInstruction(strInstructionType);
								FillExecutionCyclesDeviationInstruction(currentElementLev2, MyExecutionCyclesDeviationInstruction);
								MyRunnable->AddInstruction(MyExecutionCyclesDeviationInstruction);

							}
							else if(strInstructionType=="sw:InstructionsConstant") {
								dcExecutionCyclesConstantInstruction* MyExecutionCyclesConstantInstruction = new dcExecutionCyclesConstantInstruction(strInstructionType);
								FillExecutionCyclesConstantInstruction(currentElementLev2,MyExecutionCyclesConstantInstruction);
								MyRunnable->AddInstruction(MyExecutionCyclesConstantInstruction);
							}
							else if(strInstructionType=="sw:Group") {
								AnalyseGroup(currentElementLev2,MyAmApplication,MyRunnable);
							}else if(strInstructionType=="sw:RunnableCall"){
								string strRunnableDestination = GetAttributeAsString(currentElementLev2, ATTR_runnable);
								MyRunnable->AddRunDestination(strRunnableDestination);
							}
							else {
								cerr<<"Not recognised instruction: " << strInstructionType << endl;

							}


						}

					}

				}
				if(MyRunnable->GetID()!="") {
					MyRunnable->SetRunSource(ID);
					MyAmApplication->AddRunnable(MyRunnable,MyRunnable->GetID());
				}
				else {
					MyRunnable->SetRunSource(ID);
					MyAmApplication->AddRunnable(MyRunnable);
				}

			}
		}
	}
}

void dcAmaltheaParser::FillInterProcessActivation(DOMElement* currentElementLev4, AmTask* MyTask, AmApplication* MyAmApplication){
	string strStimulus=GetAttributeAsString(currentElementLev4,ATTR_stimulus);
	if(strStimulus=="") { //the name can be also proveded in a child with <stimulus 
		DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
		const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
		for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
		{
			DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
			if( currentNodeLev5->getNodeType() &&  // true is not NULL
				currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
			{
				DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
				if( XMLString::equals(currentElementLev5->getTagName(), TAG_stimulus))
				{
					strStimulus=GetAttributeAsString(currentElementLev5,ATTR_href);
					if(strStimulus.find("#")!=string::npos) {
						strStimulus.erase(0,strStimulus.find("#")+1);
					}

				}
			}
		}
	}
	dcActEvent* MyStimulus=MyAmApplication->GetActEvent(strStimulus);
	MyStimulus->AddSource(MyTask); 
}

void dcAmaltheaParser::ParseAmaltheaTags(DOMNodeList* const children , AmApplication* MyAmApplication){
	int nodeCount = children->getLength();

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );

			if( XMLString::equals(currentElement->getTagName(), TAG_tags))
			{
				string ID = GetAttributeAsString(currentElement,ATTR_xmi_id);
				string name = GetAttributeAsString(currentElement,ATTR_tagName);

				dcTag* tag = new dcTag(name);
				tag->SetID(ID);

				MyAmApplication->AddTag(tag);
			}
		}
	}
}

void dcAmaltheaParser::ParseAmaltheaFileTasks(DOMNodeList* const children , AmApplication* MyAmApplication){
	int nodeCount = children->getLength();

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );


			if( XMLString::equals(currentElement->getTagName(), TAG_tasks))
			{
				string temp = GetAttributeAsString(currentElement,ATTR_name);
				AmTask *MyTask = new AmTask(GetAttributeAsString(currentElement,ATTR_name));
				MyTask->SetID(GetAttributeAsString(currentElement, ATTR_xmi_id));
				string strPriority = GetAttributeAsString(currentElement,ATTR_priority);
				if(strPriority!="") {
					MyTask->SetPriority(atoi(strPriority.c_str()));
					MyAmApplication->AddProirity(atoi(strPriority.c_str()));
				}

				
				MyTask->SetTaskID(TaskCounter);
				TaskCounter = TaskCounter + 1;

				
				

				string strMultipleTaskActivationLimit = GetAttributeAsString(currentElement,ATTR_multipleTaskActivationLimit);
				if(strMultipleTaskActivationLimit!="") {
					MyTask->SetMultipleTaskActivationLimit(atoi(strMultipleTaskActivationLimit.c_str()));
				}

				string strPreemption = GetAttributeAsString(currentElement,ATTR_preemption);
				if(strPreemption!="") {
					if(strPreemption == "preemptive"){
						int counter = 0;
						counter = MyAmApplication->GetNoOfPreemptive()+1;
						MyAmApplication->SetNoOfPreemptive(counter);
					}else{
						//not premptive
						int counter = 0;
						counter =  MyAmApplication->GetNoOfNonPreemptive()+1;
						MyAmApplication->SetNoOfNonPreemptive(counter);
					}
					MyTask->SetPreemption(strPreemption);
				}

				string strTag = GetAttributeAsString(currentElement,ATTR_tags);
				if(strTag != ""){
					dcTag* tag = MyAmApplication->GetTag(strTag);
					MyTask->SetTag(tag);
				}

				const XMLCh* xmlch = currentElement->getAttribute(ATTR_stimuli);
				const char* strXmlch = XMLString::transcode(xmlch);


				std::string strStimulus(strXmlch); //deal with log stimulus ID
				if(strStimulus != ""){
					vector<std::string> strStimulusIDs = MyAmApplication->GetStimuliIDs(strStimulus);
					size_t i=0;
					for(i; i < strStimulusIDs.size(); i++){
						std::string strId(strStimulusIDs.at(i));
						//Stimulus* MyStimulus=MyAmaltheaSystem->GetStimulus(strId);
						dcActEvent* MyStimulus=MyAmApplication->GetActEvent(strId);
						MyStimulus->AddDestination(MyTask);
						MyTask->SetActEvent(MyAmApplication->GetActEvent(strId));
					}
				}



				DOMNodeList* childrenLev2 = currentElement->getChildNodes();
				const  XMLSize_t nodeCountLev2 = childrenLev2->getLength();
				for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
				{
					DOMNode* currentNodeLev2 = childrenLev2->item(xxLev2);
					if( currentNodeLev2->getNodeType() &&  // true is not NULL
						currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
						if( XMLString::equals(currentElementLev2->getTagName(), TAG_size))
						{
							MyTask->SetSize(atoi(GetAttributeAsString(currentElementLev2,ATTR_numberBits).c_str()));

						}else if( XMLString::equals(currentElementLev2->getTagName(), TAG_deadline))
						{
							string strValue = GetAttributeAsString(currentElementLev2,ATTR_value);
							string strUnit = GetAttributeAsString(currentElementLev2,ATTR_unit);

							MyAmApplication->AddDeadlines(atoi(strValue.c_str()));
							MyTask->SetDeadline(pair<int,string>(atoi(strValue.c_str()),strUnit));

						}else if(XMLString::equals(currentElementLev2->getTagName(), TAG_customProperties)){
							string custType = GetAttributeAsString(currentElementLev2,ATTR_key);
							if(custType == "Resource"){
								DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
								const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
								for( XMLSize_t xxLev3 = 0; xxLev3 < nodeCountLev3; ++xxLev3 )
								{
									DOMNode* currentNodeLev3 = childrenLev3->item(xxLev3);
									if( currentNodeLev3->getNodeType() &&  // true is not NULL
										currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
									{
										DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
										if( XMLString::equals(currentElementLev3->getTagName(), TAG_value))
										{
											DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
											const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
											for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
											{
												DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
												if( currentNodeLev4->getNodeType() &&  // true is not NULL
													currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
												{
													DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
													if( XMLString::equals(currentElementLev4->getTagName(), TAG_values))
													{
														MyTask->SetResource(GetAttributeAsString(currentElementLev4,ATTR_value));

													}
												}
											}
										}

									}
								}

							}
						}
						else if( XMLString::equals(currentElementLev2->getTagName(), TAG_callGraph))
						{

							DOMNodeList* childrenLev3 = currentElementLev2->getChildNodes();
							const  XMLSize_t nodeCountLev3 = childrenLev3->getLength();
							for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev3; ++xxLev2 )
							{
								DOMNode* currentNodeLev3 = childrenLev3->item(xxLev2);
								if( currentNodeLev3->getNodeType() &&  // true is not NULL
									currentNodeLev3->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
								{
									DOMElement* currentElementLev3 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev3 );
									if( XMLString::equals(currentElementLev3->getTagName(), TAG_graphEntries))
									{
										string strType = GetAttributeAsString(currentElementLev3, ATTR_xsi_type);
										if(strType == "sw:ProbabiltitySwitch"){
											DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
											const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
											for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
											{
												DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
												if( currentNodeLev4->getNodeType() &&  // true is not NULL
													currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
												{
													DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
													if( XMLString::equals(currentElementLev4->getTagName(), TAG_entries))
													{
														string probability = GetAttributeAsString(currentElementLev4,ATTR_probability);

														DOMNodeList* childrenLev5 = currentElementLev4->getChildNodes();
														const  XMLSize_t nodeCountLev5 = childrenLev5->getLength();
														for( XMLSize_t xxLev5 = 0; xxLev5 < nodeCountLev5; ++xxLev5 )
														{
															DOMNode* currentNodeLev5 = childrenLev5->item(xxLev5);
															if( currentNodeLev5->getNodeType() &&  // true is not NULL
																currentNodeLev5->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
															{
																DOMElement* currentElementLev5 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev5 );
																if( XMLString::equals(currentElementLev5->getTagName(), TAG_graphEntries))
																{
																	string name = GetAttributeAsString(currentElementLev5, ATTR_name);

																	DOMNodeList* childrenLev6 = currentElementLev5->getChildNodes();
																	const  XMLSize_t nodeCountLev6 = childrenLev6->getLength();
																	for( XMLSize_t xxLev6 = 0; xxLev6 < nodeCountLev6; ++xxLev6 )
																	{
																		DOMNode* currentNodeLev6 = childrenLev6->item(xxLev6);
																		if( currentNodeLev6->getNodeType() &&  // true is not NULL
																			currentNodeLev6->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
																		{
																			DOMElement* currentElementLev6 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev6 );
																			if( XMLString::equals(currentElementLev6->getTagName(), TAG_calls))
																			{
																				string strType = GetAttributeAsString(currentElementLev6,ATTR_xsi_type);
																				if(strType=="sw:TaskRunnableCall") {
																					//inherit task priority and premption
																					AmRunnable* Runnable = MyAmApplication->GetRunnable(GetAttributeAsString(currentElementLev6,ATTR_runnable));
																					Runnable->SetPriority(atoi(strPriority.c_str()));
																					Runnable->SetPreemption(strPreemption);
																					//set runnable dealine here
																					MyTask->AddRunnable(Runnable);

																				}else if(strType=="sw:InterProcessActivation"){
																					FillInterProcessActivation(currentElementLev6, MyTask, MyAmApplication);
												
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}else if(strType== "sw:CallSequence"){

											DOMNodeList* childrenLev4 = currentElementLev3->getChildNodes();
											const  XMLSize_t nodeCountLev4 = childrenLev4->getLength();
											for( XMLSize_t xxLev4 = 0; xxLev4 < nodeCountLev4; ++xxLev4 )
											{
												DOMNode* currentNodeLev4 = childrenLev4->item(xxLev4);
												if( currentNodeLev4->getNodeType() &&  // true is not NULL
													currentNodeLev4->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
												{
													DOMElement* currentElementLev4 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev4 );
													if( XMLString::equals(currentElementLev4->getTagName(), TAG_calls))
													{

														string strType = GetAttributeAsString(currentElementLev4,ATTR_xsi_type);
														if(strType=="sw:TaskRunnableCall") {
															AmRunnable* Runnable = MyAmApplication->GetRunnable(GetAttributeAsString(currentElementLev4,ATTR_runnable));
															Runnable->SetPriority(atoi(strPriority.c_str()));
															Runnable->SetPreemption(strPreemption);
															MyTask->AddRunnable(Runnable);
														}
														else if(strType=="sw:InterProcessActivation") {
															FillInterProcessActivation(currentElementLev4, MyTask, MyAmApplication);
														}
													}
												}
											}
										}


									}
								}
							}
						}
						else if( XMLString::equals(currentElementLev2->getTagName(), TAG_stimuli))
						{

							string strStimulus=GetAttributeAsString(currentElementLev2,ATTR_href);
							if(strStimulus.find("#")!=string::npos) {
								strStimulus.erase(0,strStimulus.find("#")+1);
							}

							dcActEvent* MyStimulus=MyAmApplication->GetActEvent(strStimulus);
							MyStimulus->AddDestination(MyTask);
						}
					}
				}
				MyAmApplication->AddTask(MyTask);
				//assign task deadlines to runnables
				vector<AmRunnable*> Runnables = MyTask->GetRunnables();
				if(MyTask->GetDeadlineUnit() != "" && MyTask->GetDeadlineValue() != NULL){
					string TaskDeadlineUnit = MyTask->GetDeadlineUnit();
					int TaskDeadlineValue = MyTask->GetDeadlineValue();
					for(size_t i = 0; i < Runnables.size(); i++){
						Runnables.at(i)->SetDeadline(pair<int, string>(TaskDeadlineValue, TaskDeadlineUnit));
					}

				}
			}
		}
	}
}

void dcAmaltheaParser::ParseAmaltheaFileLabels(DOMNodeList* const children , AmApplication* MyAmApplication) {

	int nodeCount = children->getLength();

	for( XMLInt32 xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
			currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );

			if( XMLString::equals(currentElement->getTagName(), TAG_labels))
			{
				dcLabel *MyLabel = new dcLabel(GetAttributeAsString(currentElement,ATTR_name));
				MyLabel->SetID(GetAttributeAsString(currentElement,ATTR_xmi_id));


				DOMNodeList* childrenLev2 = currentElement->getChildNodes();
				const  XMLSize_t nodeCountLev2 = childrenLev2->getLength();
				for( XMLSize_t xxLev2 = 0; xxLev2 < nodeCountLev2; ++xxLev2 )
				{
					DOMNode* currentNodeLev2 = childrenLev2->item(xxLev2);
					if( currentNodeLev2->getNodeType() &&  // true is not NULL
						currentNodeLev2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
					{
						DOMElement* currentElementLev2 = dynamic_cast< xercesc::DOMElement* >( currentNodeLev2 );
						if( XMLString::equals(currentElementLev2->getTagName(), TAG_size))
						{
							MyLabel->SetSize(atoi(GetAttributeAsString(currentElementLev2,ATTR_numberBits).c_str()));
						}

					}

				}
				if(MyLabel->GetID()!="") {
					MyAmApplication->AddLabel(MyLabel,MyLabel->GetID());
				}
				else {
					MyAmApplication->AddLabel(MyLabel);
				}
			}
		}
	}
}

void dcAmaltheaParser::ParseAmaltheaFile(string& FileName,AmApplication* MyAmApplication)
{
	clock_t start, end;
	start = clock();

	struct stat fileStatus;

	errno = 0;
	if(stat(FileName.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
	{
		if( errno == ENOENT )      // errno declared by include file errno.h
			throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
		else if( errno == ENOTDIR )
			throw ( std::runtime_error("A component of the path is not a directory."));
		else if( errno == ELOOP )
			throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
		else if( errno == EACCES )
			throw ( std::runtime_error("Permission denied."));
		else if( errno == ENAMETOOLONG )
			throw ( std::runtime_error("File can not be read\n"));
	}

	// Configure DOM parser.

	m_Parser->setValidationScheme( XercesDOMParser::Val_Never );
	m_Parser->setDoNamespaces( false );
	m_Parser->setDoSchema( false );
	m_Parser->setLoadExternalDTD( false );

	try
	{
		m_Parser->parse( FileName.c_str() );

		// no need to free this pointer - owned by the parent parser object
		xercesc::DOMDocument* xmlDoc = m_Parser->getDocument();

		// Get the top-level element: Name is "root". No attributes for "root"

		DOMElement* elementRoot = xmlDoc->getDocumentElement();
		if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));

		ParseAmaltheaFileHWModel(GetElementWithTaghwModel(elementRoot), MyAmApplication);
		ParseAmaltheaFileStimuli(GetElementWithTagStimuliModel(elementRoot), MyAmApplication);
		ParseAmaltheaFileLabels(GetElementWithTagswModel(elementRoot), MyAmApplication);
		ParseAmaltheaTags(GetElementWithTagswModel(elementRoot), MyAmApplication);
		ParseAmaltheaFileRunnable(GetElementWithTagswModel(elementRoot), MyAmApplication);
		ParseAmaltheaFileTasks(GetElementWithTagswModel(elementRoot),MyAmApplication);

		end = clock();


		//Dump the duration of the application parsing to the file Temporal_behaviour.txt
		


		FILE* fp_w_1;
		fp_w_1 = fopen("./Buffer/Buffer.out" , "w");
		if(fp_w_1 == NULL) 
		  {
		    perror("Buffer.out not found in the specified directory");
		  }
		fprintf(fp_w_1, "Application parse time: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
		fclose(fp_w_1);
		
		
		//cout << "Duration of application parsing: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << "\n\n";
	
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}
}

