/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qshaderprogram.h"
#include "qshaderprogram_p.h"
#include <Qt3DCore/qscenepropertychange.h>
#include <QDebug>
#include <QFile>

QT_BEGIN_NAMESPACE

namespace Qt3D {

QShaderProgramPrivate::QShaderProgramPrivate(QShaderProgram *qq)
    : QAbstractShaderPrivate(qq)
{
}

QShaderProgram::QShaderProgram(QNode *parent)
    : QAbstractShader(*new QShaderProgramPrivate(this), parent)
{
}

void QShaderProgram::copy(const QNode *ref)
{
    Q_D(QShaderProgram);
    QAbstractShader::copy(ref);
    const QShaderProgram *prog = qobject_cast<const QShaderProgram *>(ref);
    if (prog != Q_NULLPTR) {
        d->m_vertexSourceFile = prog->d_func()->m_vertexSourceFile;
        d->m_tessControlSourceFile = prog->d_func()->m_tessControlSourceFile;
        d->m_tessEvalSourceFile = prog->d_func()->m_tessEvalSourceFile;
        d->m_geometrySourceFile = prog->d_func()->m_geometrySourceFile;
        d->m_fragmentSourceFile = prog->d_func()->m_fragmentSourceFile;
        d->m_computeSourceFile = prog->d_func()->m_computeSourceFile;

        d->m_vertexShaderCode = prog->d_func()->m_vertexShaderCode;
        d->m_tessControlShaderCode = prog->d_func()->m_tessControlShaderCode;
        d->m_tessEvalShaderCode = prog->d_func()->m_tessEvalShaderCode;
        d->m_geometryShaderCode = prog->d_func()->m_geometryShaderCode;
        d->m_fragmentShaderCode = prog->d_func()->m_fragmentShaderCode;
        d->m_computeShaderCode = prog->d_func()->m_computeShaderCode;
    }
}

QShaderProgram::QShaderProgram(QShaderProgramPrivate &dd, QNode *parent)
    : QAbstractShader(dd, parent)
{
}

QShaderProgram *QShaderProgram::doClone(QNode *clonedParent) const
{
    return new QShaderProgram(clonedParent);
}

void QShaderProgram::setVertexShaderSourceFile(const QString& vertexShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (vertexShaderSourceFile != d->m_vertexSourceFile) {
        d->m_vertexSourceFile = vertexShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("vertexSourceFile"),
                             vertexShaderSourceFile);
        emit vertexShaderSourceFileChanged();
    }
}

QString QShaderProgram::vertexShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_vertexSourceFile;
}

void QShaderProgram::setTessellationControlShaderSourceFile(const QString &tessellationControlShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (tessellationControlShaderSourceFile != d->m_tessControlSourceFile) {
        d->m_tessControlSourceFile = tessellationControlShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("tessellationControlShaderSourceFile"),
                             tessellationControlShaderSourceFile);
        emit tessellationControlShaderSourceFileChanged();
    }
}

QString QShaderProgram::tessellationControlShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_tessControlSourceFile;
}

void QShaderProgram::setTessellationEvaluationShaderSourceFile(const QString &tessellationEvaluationShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (tessellationEvaluationShaderSourceFile != d->m_tessEvalSourceFile) {
        d->m_tessEvalSourceFile = tessellationEvaluationShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("tessellationEvaluationShaderSourceFile"),
                             tessellationEvaluationShaderSourceFile);
        emit tessellationEvaluationShaderSourceFileChanged();
    }
}

QString QShaderProgram::tessellationEvaluationShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_tessEvalSourceFile;
}

void QShaderProgram::setGeometryShaderSourceFile(const QString &geometryShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (geometryShaderSourceFile != d->m_geometrySourceFile) {
        d->m_geometrySourceFile = geometryShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("geometryShaderSourceFile"),
                             geometryShaderSourceFile);
        emit geometryShaderSourceFileChanged();
    }
}

QString QShaderProgram::geometryShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_geometrySourceFile;
}

void QShaderProgram::setFragmentShaderSourceFile(const QString& fragmentShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (fragmentShaderSourceFile != d->m_fragmentSourceFile) {
        d->m_fragmentSourceFile = fragmentShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("fragmentSourceFile"),
                             fragmentShaderSourceFile);
        emit fragmentShaderSourceFileChanged();
    }
}

QString QShaderProgram::fragmentShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_fragmentSourceFile;
}

void QShaderProgram::setComputeShaderSourceFile(const QString &computeShaderSourceFile)
{
    Q_D(QShaderProgram);
    if (computeShaderSourceFile != d->m_computeSourceFile) {
        d->m_computeSourceFile = computeShaderSourceFile;
        notifyPropertyChange(QByteArrayLiteral("computeShaderSourceFile"),
                             computeShaderSourceFile);
        emit computeShaderSourceFileChanged();
    }
}

QString QShaderProgram::computeShaderSourceFile() const
{
    Q_D(const QShaderProgram);
    return d->m_computeSourceFile;
}

void QShaderProgram::setShaderSourceFile(ShaderType type, const QString &sourceFile)
{
    switch (type) {
    case Vertex:
        setVertexShaderSourceFile(sourceFile);
        break;
    case TessellationControl:
        setTessellationControlShaderSourceFile(sourceFile);
        break;
    case TessellationEvaluation:
        setTessellationEvaluationShaderSourceFile(sourceFile);
        break;
    case Geometry:
        setGeometryShaderSourceFile(sourceFile);
        break;
    case Fragment:
        setFragmentShaderSourceFile(sourceFile);
        break;
    case Compute:
        setComputeShaderSourceFile(sourceFile);
        break;
    default:
        Q_UNREACHABLE();
    }
}

QString QShaderProgram::shaderSourceFile(ShaderType type) const
{
    Q_D(const QShaderProgram);
    switch (type) {
    case Vertex:
        return d->m_vertexSourceFile;
    case TessellationControl:
        return d->m_tessControlSourceFile;
    case TessellationEvaluation:
        return d->m_tessEvalSourceFile;
    case Geometry:
        return d->m_geometrySourceFile;
    case Fragment:
        return d->m_fragmentSourceFile;
    case Compute:
        return d->m_computeSourceFile;
    default:
        Q_UNREACHABLE();
    }
}

/*!
 * Sets the vertexShader from raw data in \a vertexShader.
 */
void QShaderProgram::setVertexShaderCode(const QByteArray &vertexShaderCode)
{
    Q_D(QShaderProgram);
    if (vertexShaderCode != d->m_vertexShaderCode) {
        d->m_vertexShaderCode = vertexShaderCode;
        notifyPropertyChange(QByteArrayLiteral("vertexSourceCode"),
                             vertexShaderCode);
        emit vertexShaderCodeChanged();
    }
}

QByteArray QShaderProgram::vertexShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_vertexShaderCode;
}

void QShaderProgram::setTessellationControlShaderCode(const QByteArray &tessellationControlShaderCode)
{
    Q_D(QShaderProgram);
    if (tessellationControlShaderCode != d->m_tessControlShaderCode) {
        d->m_tessControlShaderCode = tessellationControlShaderCode;
        notifyPropertyChange(QByteArrayLiteral("tessellationControlSourceCode"),
                             tessellationControlShaderCode);
        emit tessellationControlShaderCodeChanged();
    }
}

QByteArray QShaderProgram::tessellationControlShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_tessControlShaderCode;
}

void QShaderProgram::setTessellationEvaluationShaderCode(const QByteArray &tessellationEvaluationShaderCode)
{
    Q_D(QShaderProgram);
    if (tessellationEvaluationShaderCode != d->m_tessEvalShaderCode) {
        d->m_tessEvalShaderCode = tessellationEvaluationShaderCode;
        notifyPropertyChange(QByteArrayLiteral("tessellationEvaluationSourceCode"),
                             tessellationEvaluationShaderCode);
        emit tessellationEvaluationShaderCodeChanged();
    }
}

QByteArray QShaderProgram::tessellationEvaluationShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_tessEvalShaderCode;
}

void QShaderProgram::setGeometryShaderCode(const QByteArray &geometryShaderCode)
{
    Q_D(QShaderProgram);
    if (geometryShaderCode != d->m_geometryShaderCode) {
        d->m_geometryShaderCode = geometryShaderCode;
        notifyPropertyChange(QByteArrayLiteral("geometrySourceCode"),
                             geometryShaderCode);
        emit geometryShaderCodeChanged();
    }
}

QByteArray QShaderProgram::geometryShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_geometryShaderCode;
}

/*!
 * Sets the fragmentShader from raw data in \a fragmentShader.
 */
void QShaderProgram::setFragmentShaderCode(const QByteArray &fragmentShaderCode)
{
    Q_D(QShaderProgram);
    if (fragmentShaderCode != d->m_fragmentShaderCode) {
        d->m_fragmentShaderCode = fragmentShaderCode;
        notifyPropertyChange(QByteArrayLiteral("fragmentSourceCode"),
                             fragmentShaderCode);
        emit fragmentShaderCodeChanged();
    }
}

QByteArray QShaderProgram::fragmentShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_fragmentShaderCode;
}

void QShaderProgram::setComputeShaderCode(const QByteArray &computeShaderCode)
{
    Q_D(QShaderProgram);
    if (computeShaderCode != d->m_computeShaderCode) {
        d->m_computeShaderCode = computeShaderCode;
        notifyPropertyChange(QByteArrayLiteral("computeSourceCode"),
                             computeShaderCode);
        emit computeShaderCodeChanged();
    }
}

QByteArray QShaderProgram::computeShaderCode() const
{
    Q_D(const QShaderProgram);
    return d->m_computeShaderCode;
}

void QShaderProgram::setShaderCode(ShaderType type, const QByteArray &shaderCode)
{
    switch (type) {
    case Vertex:
        setVertexShaderCode(shaderCode);
        break;
    case TessellationControl:
        setTessellationControlShaderCode(shaderCode);
        break;
    case TessellationEvaluation:
        setTessellationEvaluationShaderCode(shaderCode);
        break;
    case Geometry:
        setGeometryShaderCode(shaderCode);
        break;
    case Fragment:
        setFragmentShaderCode(shaderCode);
        break;
    case Compute:
        setComputeShaderCode(shaderCode);
        break;
    default:
        Q_UNREACHABLE();
    }
}

QByteArray QShaderProgram::shaderCode(ShaderType type) const
{
    Q_D(const QShaderProgram);
    switch (type) {
    case Vertex:
        return d->m_vertexShaderCode;
    case TessellationControl:
        return d->m_tessControlShaderCode;
    case TessellationEvaluation:
        return d->m_tessEvalShaderCode;
    case Geometry:
        return d->m_geometryShaderCode;
    case Fragment:
        return d->m_fragmentShaderCode;
    case Compute:
        return d->m_computeShaderCode;
    default:
        Q_UNREACHABLE();
    }
}

} // of namespace Qt3D

QT_END_NAMESPACE
