/****************************************************************************

This file is part of the wolfenqt project on http://qt.gitorious.org.

Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).*
All rights reserved.

Contact:  Nokia Corporation (qt-info@nokia.com)**

You may use this file under the terms of the BSD license as follows:

"Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
* Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the
* names of its contributors may be used to endorse or promote products
* derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE."

****************************************************************************/
#include "model.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QVarLengthArray>

#ifndef QT_NO_OPENGL
#if !defined QT_OPENGL_ES_2 && !defined Q_WS_MAC
#include <GL/glew.h>
#endif
#include <QtOpenGL>
#endif

Model::Model(const QString &filePath)
    : m_fileName(QFileInfo(filePath).fileName())
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QVector3D boundsMin( 1e9, 1e9, 1e9);
    QVector3D boundsMax(-1e9,-1e9,-1e9);

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString input = in.readLine();
        if (input.isEmpty() || input[0] == '#')
            continue;

        QTextStream ts(&input);
        QString id;
        ts >> id;
        if (id == "v") {
            QVector3D p;
            for (int i = 0; i < 3; ++i) {
                ts >> ((float *)&p)[i];
                ((float *)&boundsMin)[i] = qMin(((float *)&boundsMin)[i], ((float *)&p)[i]);
                ((float *)&boundsMax)[i] = qMax(((float *)&boundsMax)[i], ((float *)&p)[i]);
            }
            m_points << p;
        } else if (id == "f" || id == "fo") {
            QVarLengthArray<int, 4> p;

            while (!ts.atEnd()) {
                QString vertex;
                ts >> vertex;
                const int vertexIndex = vertex.split('/').value(0).toInt();
                if (vertexIndex)
                    p.append(vertexIndex > 0 ? vertexIndex - 1 : m_points.size() + vertexIndex);
            }

            for (int i = 0; i < p.size(); ++i) {
                const int edgeA = p[i];
                const int edgeB = p[(i + 1) % p.size()];

                if (edgeA < edgeB)
                    m_edgeIndices << edgeA << edgeB;
            }

            for (int i = 0; i < 3; ++i)
                m_pointIndices << p[i];

            if (p.size() == 4)
                for (int i = 0; i < 3; ++i)
                    m_pointIndices << p[(i + 2) % 4];
        }
    }

    const QVector3D bounds = boundsMax - boundsMin;
    const qreal scale = 1 / qMax(bounds.x() / 1, qMax(bounds.y(), bounds.z() / 1));
    for (int i = 0; i < m_points.size(); ++i)
        m_points[i] = (m_points[i] - (boundsMin + bounds * 0.5)) * scale;

    m_size = bounds * scale;

    m_normals.resize(m_points.size());
    for (int i = 0; i < m_pointIndices.size(); i += 3) {
        const QVector3D a = m_points.at(m_pointIndices.at(i));
        const QVector3D b = m_points.at(m_pointIndices.at(i+1));
        const QVector3D c = m_points.at(m_pointIndices.at(i+2));

        const QVector3D normal = QVector3D::crossProduct(b - a, c - a).normalized();

        for (int j = 0; j < 3; ++j)
            m_normals[m_pointIndices.at(i + j)] += normal;
    }

    for (int i = 0; i < m_normals.size(); ++i)
        m_normals[i] = m_normals[i].normalized();
}

QVector3D Model::size() const
{
    return m_size;
}

void Model::render(bool wireframe, bool normals) const
{
#ifdef QT_NO_OPENGL
    Q_UNUSED(wireframe);
    Q_UNUSED(normals);
#else
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GEQUAL);
    glDepthMask(true);

#ifdef QT_OPENGL_ES_2
    GLenum elementType = GL_UNSIGNED_SHORT;
#else
    GLenum elementType = GL_UNSIGNED_INT;
#endif

    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (float *)m_points.data());
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (float *)m_normals.data());

    if (wireframe)
        glDrawElements(GL_LINES, m_edgeIndices.size(), elementType, m_edgeIndices.data());
    else
        glDrawElements(GL_TRIANGLES, m_pointIndices.size(), elementType, m_pointIndices.data());

    if (normals) {
        QVector<QVector3D> points;
        QVector<QVector3D> normals;
        for (int i = 0; i < m_normals.size(); ++i) {
            points << m_points.at(i) << (m_points.at(i) + m_normals.at(i) * 0.02f);
            normals << m_normals.at(i) << m_normals.at(i);
        }

        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (float *)points.data());
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (float *)normals.data());
        glDrawArrays(GL_LINES, 0, points.size());
    }

    ////glDisableVertexAttribArray(1);
    ////glDisableVertexAttribArray(0);
    glDisable(GL_DEPTH_TEST);
#endif
}

void Model::render(QPainter *painter, const QMatrix4x4 &matrix, bool normals) const
{
    m_mapped.resize(m_points.size());
    for (int i = 0; i < m_points.size(); ++i)
        m_mapped[i] = matrix.map(m_points.at(i));

    m_lines.clear();
    for (int i = 0; i < m_edgeIndices.size(); i += 2) {
        const QVector3D a = m_mapped.at(m_edgeIndices.at(i));
        const QVector3D b = m_mapped.at(m_edgeIndices.at(i+1));

        if (a.z() > 0 && b.z() > 0)
            m_lines << QLineF(a.toPointF(), b.toPointF());
    }

    if (normals) {
        for (int i = 0; i < m_normals.size(); ++i) {
            const QVector3D a = m_mapped.at(i);
            const QVector3D b = matrix.map(m_points.at(i) + m_normals.at(i) * 0.02f);

            if (a.z() > 0 && b.z() > 0)
                m_lines << QLineF(a.toPointF(), b.toPointF());
        }
    }

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->drawLines(m_lines);
}
