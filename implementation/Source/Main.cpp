/*
 * JumpSeat
 * Copyright (C) 2015 Petter Holmström
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../JuceLibraryCode/JuceHeader.h"

#include "ModemIO.h"
#include "AlertDispatcher.h"
#include "AlertTypeRepository.h"
#include "AlertLogger.h"
#include "ResourceRepository.h"
#include "SMSLogger.h"

#include "MainComponent.h"

class JumpSeatApplication: public JUCEApplication {
public:
    JumpSeatApplication() {}

    const String getApplicationName() override {
        return ProjectInfo::projectName;
    }
    
    const String getApplicationVersion() override {
        return ProjectInfo::versionString;
    }
    
    bool moreThanOneInstanceAllowed() override {
        return false;
    }

    void initialise(const String& commandLine) override {
        db = new JumpSeat::DB("/Users/petterprivate/Projects/JumpSeat/jumpseat.db");
        modemIO = new JumpSeat::ModemIO();
        smsLogger = new JumpSeat::SMSLogger(*db, *modemIO);
        alertTypeRepository = new JumpSeat::AlertTypeRepository(*db);
        resourceRepository = new JumpSeat::ResourceRepository(*db);
        
        alertDispatcher = new JumpSeat::AlertDispatcher(*alertTypeRepository, *modemIO);
        
        alertDispatcher->setAlertRegex(
            std::regex("^TKU ([A-Za-z\\s]*[0-9]+)[\\w\\s],([\\w\\s]*,[\\w\\s]*),([\\w\\s]*,[\\w\\s]*,[\\w\\s]*),(.*)"),
            std::vector<JumpSeat::AlertField> {
                JumpSeat::AlertField::code,
                JumpSeat::AlertField::municipality,
                JumpSeat::AlertField::address,
                JumpSeat::AlertField::details
            });
        
//        auto responseDispatcher = JumpSeat::ResponseDispatcher();
        alertLogger = new JumpSeat::AlertLogger(*db, *alertDispatcher);
        
        // Set up handlers
//        modemIO->addOnSMSHandler(smsLogger.get());
//        modemIO->addOnSMSHandler(boost::bind(&JumpSeat::AlertDispatcher::onReceiveSMS, *alertDispatcher, _1));
//        modemIO.addOnSMSHandler(boost::bind(&JumpSeat::ResponseDispatcher::onReceiveSMS, &responseDispatcher, _1));
        
        //alertDispatcher->addOnAlertHandler(boost::bind(&JumpSeat::AlertLogger::onReceiveAlert, &alertLogger, _1));
        
        mainWindow = new MainWindow(getApplicationName());
    }

    void shutdown() override {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override {
        quit();
    }

    void anotherInstanceStarted(const String& commandLine) override {
    }

    /**
     * This class implements the desktop window that contains an instance of
     * our MainContentComponent class.
     */
    class MainWindow: public DocumentWindow {
    public:
        MainWindow(String name): DocumentWindow(name,
                                                Colours::lightgrey,
                                                DocumentWindow::allButtons) {
            MainContentComponent* mainContentComponent = new MainContentComponent();
            setUsingNativeTitleBar(true);
            setContentOwned(mainContentComponent, true);
            #if JUCE_MAC
                MenuBarModel::setMacMainMenu(mainContentComponent);
            #else
                setMenuBar(mainContentComponent);
            #endif

            setResizable(true, true);
            setVisible(true);
            setFullScreen(true);
        }
        
        ~MainWindow() {
            #if JUCE_MAC
                MenuBarModel::setMacMainMenu(nullptr);
            #else
                setMenuBar(nullptr);
            #endif
        }

        void closeButtonPressed() override {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<JumpSeat::DB> db;
    ScopedPointer<JumpSeat::AlertTypeRepository> alertTypeRepository;
    ScopedPointer<JumpSeat::ResourceRepository> resourceRepository;
    ScopedPointer<JumpSeat::ModemIO> modemIO;
    ScopedPointer<JumpSeat::SMSLogger> smsLogger;
    ScopedPointer<JumpSeat::AlertDispatcher> alertDispatcher;
    ScopedPointer<JumpSeat::AlertLogger> alertLogger;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (JumpSeatApplication)
