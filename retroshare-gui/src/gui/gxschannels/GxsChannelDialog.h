/*******************************************************************************
 * retroshare-gui/src/gui/gxschannels/GxsChannelDialog.h                       *
 *                                                                             *
 * Copyright 2013 by Robert Fernie     <retroshare.project@gmail.com>          *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#ifndef _GXS_CHANNEL_DIALOG_H
#define _GXS_CHANNEL_DIALOG_H

#include "gui/gxs/GxsGroupFrameDialog.h"

#define IMAGE_GXSCHANNELS       ":/icons/png/channel.png"

class GxsChannelDialog : public GxsGroupFrameDialog
{
	Q_OBJECT

public:
	/** Default Constructor */
	GxsChannelDialog(QWidget *parent = 0);
	/** Default Destructor */
	~GxsChannelDialog();

	virtual QIcon iconPixmap() const { return QIcon(IMAGE_GXSCHANNELS) ; } //MainPage
	virtual QString pageName() const { return tr("Channels") ; } //MainPage
	virtual QString helpText() const { return ""; } //MainPage

	void shareOnChannel(const RsGxsGroupId& channel_id, const QList<RetroShareLink>& file_link) ;

protected:
	/* GxsGroupFrameDialog */
    virtual bool getDistantSearchResults(TurtleRequestId id, std::map<RsGxsGroupId, RsGxsGroupSearchResults> &group_infos) override;
	virtual RsGxsGenericGroupData *getDistantSearchResultGroupData(const RsGxsGroupId& group_id) override;

	virtual TurtleRequestId distantSearch(const QString& search_string) override;
    virtual void checkRequestGroup(const RsGxsGroupId& grpId) override ;
	virtual void clearDistantSearchResults(TurtleRequestId id) override;

    // Implementation of some abstract methods in GxsGroupFrameDialog

	virtual QString getHelpString() const override;
	GroupFrameSettings::Type groupFrameSettingsType() override { return GroupFrameSettings::Channel; }
	RetroShareLink::enumType getLinkType() override { return RetroShareLink::TYPE_CHANNEL; }
	void groupInfoToGroupItemInfo(const RsGxsGenericGroupData *groupData, GroupItemInfo &groupItemInfo) override;
    const std::set<TurtleRequestId> getSearchRequests() const override { return mSearchResults ; }
	UserNotify *createUserNotify(QObject *parent) override;
	bool getGroupData(std::list<RsGxsGenericGroupData*>& groupInfo) override;
	bool getGroupStatistics(const RsGxsGroupId& groupId,GxsGroupStatistic& stat) override;

private slots:
	void toggleAutoDownload();
        void setDefaultDirectory();
        void setDownloadDirectory();
        void specifyDownloadDirectory();

private:
	/* GxsGroupFrameDialog */
	virtual QString text(TextType type);
	virtual QString icon(IconType type);
	virtual QString settingsGroupName() { return "ChannelDialog"; }
	virtual GxsGroupDialog *createNewGroupDialog();
	virtual GxsGroupDialog *createGroupDialog(GxsGroupDialog::Mode mode, RsGxsGroupId groupId);
	virtual int shareKeyType();
	virtual GxsMessageFrameWidget *createMessageFrameWidget(const RsGxsGroupId &groupId);
	virtual void groupTreeCustomActions(RsGxsGroupId grpId, int subscribeFlags, QList<QAction*> &actions);
	virtual RsGxsCommentService *getCommentService();
	virtual QWidget *createCommentHeaderWidget(const RsGxsGroupId &grpId, const RsGxsMessageId &msgId);
	virtual uint32_t requestGroupSummaryType() { return GXS_REQUEST_TYPE_GROUP_DATA; } // request complete group data

	void handleEvent_main_thread(std::shared_ptr<const RsEvent> event);

    std::set<TurtleRequestId> mSearchResults;

    RsEventsHandlerId_t mEventHandlerId;
};

#endif
