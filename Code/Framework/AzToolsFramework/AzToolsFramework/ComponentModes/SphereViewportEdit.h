/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzToolsFramework/Manipulators/LinearManipulator.h>
#include <AzToolsFramework/ComponentModes/BaseShapeViewportEdit.h>

namespace AzToolsFramework
{
    //! Wraps a linear manipulator, providing a viewport experience for modifying the radius of a sphere.
    //! It is designed to be usable either by a component mode or by other contexts which are not associated with a
    //! particular component, so editing does not rely on an EntityComponentIdPair or other component-based identifier.
    class SphereViewportEdit : public BaseShapeViewportEdit
    {
    public:
        void InstallGetRotationOffset(AZStd::function<AZ::Quaternion()> getRotationOffset);
        void InstallGetSphereRadius(AZStd::function<float()> getSphereRadius);
        void InstallSetSphereRadius(AZStd::function<void(float)> setSphereRadius);

        // BaseShapeViewportEdit overrides ...
        void Setup(const ManipulatorManagerId manipulatorManagerId) override;
        void Teardown() override;
        void UpdateManipulators() override;
        void ResetValuesImpl() override;
        void AddEntityComponentIdPairImpl(const AZ::EntityComponentIdPair& entityComponentIdPair) override;

        void OnCameraStateChanged(const AzFramework::CameraState& cameraState);
    private:
        AZ::Quaternion GetRotationOffset() const;
        float GetSphereRadius() const;
        void SetSphereRadius(float radius);

        AZ::Transform GetLocalTransform() const;

        void SetupRadiusManipulator(
            const ManipulatorManagerId manipulatorManagerId,
            const AZ::Transform& worldTransform,
            const AZ::Transform& localTransform,
            const AZ::Vector3& nonUniformScale);
        void OnRadiusManipulatorMoved(const LinearManipulator::Action& action);

        AZStd::shared_ptr<LinearManipulator> m_radiusManipulator;

        AZStd::function<AZ::Quaternion()> m_getRotationOffset;
        AZStd::function<float()> m_getSphereRadius;
        AZStd::function<void(float)> m_setSphereRadius;
    };
} // namespace AzToolsFramework
