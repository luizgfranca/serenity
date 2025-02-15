/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Spencer Dixon <spencercdixon@gmail.com>
 * Copyright (c) 2021, Liav A. <liavalb@hotmail.co.il>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Kernel/FileSystem/ProcFS/FileSystem.h>
#include <Kernel/FileSystem/ProcFS/Inode.h>

namespace Kernel {

ErrorOr<NonnullLockRefPtr<FileSystem>> ProcFS::try_create()
{
    return TRY(adopt_nonnull_lock_ref_or_enomem(new (nothrow) ProcFS));
}

ProcFS::ProcFS() = default;
ProcFS::~ProcFS() = default;

ErrorOr<NonnullRefPtr<Inode>> ProcFS::get_inode(InodeIdentifier inode_id) const
{
    if (inode_id.index() == 1)
        return *m_root_inode;
    return TRY(adopt_nonnull_ref_or_enomem(new (nothrow) ProcFSInode(const_cast<ProcFS&>(*this), inode_id.index())));
}

ErrorOr<void> ProcFS::initialize()
{
    m_root_inode = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) ProcFSInode(const_cast<ProcFS&>(*this), 1)));
    return {};
}

Inode& ProcFS::root_inode()
{
    return *m_root_inode;
}

}
