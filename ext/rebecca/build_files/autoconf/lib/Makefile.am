AUTOMAKE_OPTIONS = gnu

lib_LTLIBRARIES = librebecca-mt.la
librebecca_mt_la_SOURCES = ../../../src/rebecca/AimlFacade.cpp \
							../../../src/rebecca/GraphBuilder.cpp \
                            ../../../src/rebecca/StringPimpl.cpp \
							../../../src/rebecca/framework/AIML.cpp \
                            ../../../src/rebecca/framework/Bot.cpp \
                            ../../../src/rebecca/framework/Category.cpp \
                            ../../../src/rebecca/framework/Condition.cpp \
                            ../../../src/rebecca/framework/Date.cpp \
                            ../../../src/rebecca/framework/Formal.cpp \
                            ../../../src/rebecca/framework/Gender.cpp \
                            ../../../src/rebecca/framework/Get.cpp \
                            ../../../src/rebecca/framework/Gossip.cpp \
                            ../../../src/rebecca/framework/GraphBuilderFramework.cpp \
                            ../../../src/rebecca/framework/Id.cpp \
                            ../../../src/rebecca/framework/InnerAIML.cpp \
                            ../../../src/rebecca/framework/InnerCategory.cpp \
                            ../../../src/rebecca/framework/InnerTemplaListImpl.cpp \
                            ../../../src/rebecca/framework/InnerTemplate.cpp \
                            ../../../src/rebecca/framework/InnerTopic.cpp \
                            ../../../src/rebecca/framework/Input.cpp \
							../../../src/rebecca/framework/Learn.cpp \
                            ../../../src/rebecca/framework/Li.cpp \
                            ../../../src/rebecca/framework/LowerCase.cpp \
                            ../../../src/rebecca/framework/NonImplemented.cpp \
                            ../../../src/rebecca/framework/Pattern.cpp \
                            ../../../src/rebecca/framework/PatternSideThat.cpp \
                            ../../../src/rebecca/framework/Person2.cpp \
                            ../../../src/rebecca/framework/Person.cpp \
                            ../../../src/rebecca/framework/PlainWord.cpp \
                            ../../../src/rebecca/framework/Random.cpp \
                            ../../../src/rebecca/framework/Sentence.cpp \
                            ../../../src/rebecca/framework/Set.cpp \
                            ../../../src/rebecca/framework/Size.cpp \
                            ../../../src/rebecca/framework/Srai.cpp \
                            ../../../src/rebecca/framework/Star.cpp \
                            ../../../src/rebecca/framework/System.cpp \
                            ../../../src/rebecca/framework/Tag.cpp \
                            ../../../src/rebecca/framework/Template.cpp \
                            ../../../src/rebecca/framework/TemplateSideThat.cpp \
                            ../../../src/rebecca/framework/ThatStar.cpp \
                            ../../../src/rebecca/framework/Think.cpp \
                            ../../../src/rebecca/framework/Topic.cpp \
                            ../../../src/rebecca/framework/TopicStar.cpp \
                            ../../../src/rebecca/framework/UpperCase.cpp \
							../../../src/rebecca/framework/Version.cpp \
                            ../../../src/rebecca/impl/ConfigurationHandler.cpp \
                            ../../../src/rebecca/impl/ConfigurationHandlerError.cpp \
                            ../../../src/rebecca/impl/CustomTagWithDelete.cpp \
                            ../../../src/rebecca/impl/Factory.cpp \
                            ../../../src/rebecca/impl/getStringFromSentence.cpp \
                            ../../../src/rebecca/impl/GraphBuilderAIML.cpp \
                            ../../../src/rebecca/impl/GraphBuilderInternal.cpp \
                            ../../../src/rebecca/impl/GraphHandler.cpp \
                            ../../../src/rebecca/impl/GraphHandlerError.cpp \
                            ../../../src/rebecca/impl/NodeMapper.cpp \
                            ../../../src/rebecca/impl/PrototypeFactory.cpp \
                            ../../../src/rebecca/impl/utils/Logging.cpp \
                            ../../../src/rebecca/impl/utils/StackTrace.cpp \
                            ../../../src/rebecca/impl/utils/Transcode.cpp

librebecca_mt_la_LDFLAGS = -version-info 0:0:0

INCLUDES=-I../../../include

confdir=${datadir}/Rebecca/conf
conf_DATA = ../../../conf/*.xml\
            ../../../conf/README.txt


picturesdir=${datadir}/Rebecca/resources/pictures
pictures_DATA =../../../resources/pictures/*.png

schemadir=${datadir}/Rebecca/resources/schema
schema_DATA =../../../resources/schema/*.xsd\
             ../../../resources/schema/README.txt

testingdir=${datadir}/Rebecca/resources/testing
testing_DATA =../../../resources/testing/AIML.aiml\
              ../../../resources/testing/AIML.xml\
              ../../../resources/testing/README.txt\
			  ../../../resources/testing/header.htm\
			  ../../../resources/testing/footer.htm

aimldir=${datadir}/Rebecca/aiml/annotated_alice
aiml_DATA =../../../aiml/annotated_alice/*.aiml

includeapidir=${includedir}/rebecca
includeapi_DATA = ../../../include/rebecca/*.h

includeFrameworkdir=${includedir}/rebecca/framework
includeFramework_DATA=../../../include/rebecca/framework/*.h

readmebinreleasedir=${datadir}/Rebecca/bin/release
readmebinrelease_DATA=../../../bin/release/README.txt

readmeaimldir=${datadir}/Rebecca/aiml
readmeaiml_DATA=../../../aiml/README.txt

