/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QTest>
#include <Qt3DCore/private/qnode_p.h>
#include <Qt3DCore/private/qscene_p.h>
#include <Qt3DCore/qentity.h>

#include <Qt3DRender/qrendertargetselector.h>
#include <Qt3DRender/private/qrendertargetselector_p.h>
#include <Qt3DRender/qrendertarget.h>
#include "testarbiter.h"

class tst_QRenderTargetSelector: public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void checkSaneDefaults()
    {
        QScopedPointer<Qt3DRender::QRenderTargetSelector> defaultTargetSelector(new Qt3DRender::QRenderTargetSelector);

        QVERIFY(defaultTargetSelector->target() == nullptr);
        QCOMPARE(defaultTargetSelector->outputs().count(), 0);
    }

    void checkPropertyUpdates()
    {
        // GIVEN
        TestArbiter arbiter;
        QScopedPointer<Qt3DRender::QRenderTargetSelector> renderTargetSelector(new Qt3DRender::QRenderTargetSelector());
        arbiter.setArbiterOnNode(renderTargetSelector.data());

        // WHEN
        Qt3DRender::QRenderTarget *target = new Qt3DRender::QRenderTarget();
        renderTargetSelector->setTarget(target);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 1);
        QCOMPARE(arbiter.dirtyNodes().front(), renderTargetSelector.data());

        arbiter.clear();

        // WHEN
        renderTargetSelector->setTarget(target);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 0);

        // WHEN
        renderTargetSelector->setTarget(nullptr);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 1);
        QCOMPARE(arbiter.dirtyNodes().front(), renderTargetSelector.data());

        arbiter.clear();

        // WHEN
        QVector<Qt3DRender::QRenderTargetOutput::AttachmentPoint> outputs;
        outputs << Qt3DRender::QRenderTargetOutput::Color0 << Qt3DRender::QRenderTargetOutput::Depth;
        renderTargetSelector->setOutputs(outputs);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 1);
        QCOMPARE(arbiter.dirtyNodes().front(), renderTargetSelector.data());

        arbiter.clear();

        // WHEN
        renderTargetSelector->setOutputs(outputs);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 0);

        // WHEN
        renderTargetSelector->setOutputs(QVector<Qt3DRender::QRenderTargetOutput::AttachmentPoint>());
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.dirtyNodes().size(), 1);
        QCOMPARE(arbiter.dirtyNodes().front(), renderTargetSelector.data());

        arbiter.clear();
    }

    void checkRenderTargetBookkeeping()
    {
        // GIVEN
        QScopedPointer<Qt3DRender::QRenderTargetSelector> targetSelector(new Qt3DRender::QRenderTargetSelector);
        {
            // WHEN
            Qt3DRender::QRenderTarget target;
            targetSelector->setTarget(&target);

            // THEN
            QCOMPARE(target.parent(), targetSelector.data());
            QCOMPARE(targetSelector->target(), &target);
        }
        // THEN (Should not crash and effect be unset)
        QVERIFY(targetSelector->target() == nullptr);

        {
            // WHEN
            Qt3DRender::QRenderTargetSelector someOtherTargetSelector;
            QScopedPointer<Qt3DRender::QRenderTarget> target(new Qt3DRender::QRenderTarget(&someOtherTargetSelector));
            targetSelector->setTarget(target.data());

            // THEN
            QCOMPARE(target->parent(), &someOtherTargetSelector);
            QCOMPARE(targetSelector->target(), target.data());

            // WHEN
            targetSelector.reset();
            target.reset();

            // THEN Should not crash when the target is destroyed (tests for failed removal of destruction helper)
        }
    }
};

QTEST_MAIN(tst_QRenderTargetSelector)

#include "tst_qrendertargetselector.moc"
